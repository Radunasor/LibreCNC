#include <string.h>

#include "gcode.h"
#include "parser.h"
#include "g_command.h"

#define CHECK_INITIALIIZED LC_ASSERT(initialized, "GCODE module not initialized!");

static bool initialized = false;
static lc_gcode_user_handler_cb_t user_handler_cb = NULL;

static lc_gcode_obj_t parsed_command = {
    .command_number = 0,
    .command_type = LC_GCODE_TYPE_NONE,
    .subcommand_existed = false,
    .sub_command_number = 0,
};

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static bool lc_gcode_parse_line(char *line, size_t line_num);
/******************************************************/

void lc_gcode_init()
{
    if (initialized)
        return;

    initialized = true;
}

void lc_gcode_deinit()
{
    if (!initialized)
        return;

    user_handler_cb = NULL;
    initialized = false;
}

bool lc_gcode_get_initialized()
{
    return initialized;
}

bool lc_gcode_process_line(const char *line, size_t line_num)
{
    CHECK_INITIALIIZED

    if (!line)
        return false;

    char clipped_line[LC_GCODE_MAX_LINE_LENTGH] = {0};
    memcpy(clipped_line, line, LC_GCODE_MAX_LINE_LENTGH);
    clipped_line[LC_GCODE_MAX_LINE_LENTGH - 1] = '\0';

    return lc_gcode_parse_line(clipped_line, line_num);
}

void lc_gcode_set_handler_callback(lc_gcode_user_handler_cb_t cb)
{
    if (cb)
        user_handler_cb = cb;
}

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static bool lc_gcode_parse_line(char *line, size_t line_num)
{
    if (!user_handler_cb)
        LC_LOG_WARN("GCODE USER CALLBACK HANDLER HAS NOT BEEN SET!");

    lc_gcode_parser_mark_comments(line);

    lc_gcode_command_type_t lc_gcode_command_type_arr[] = {
#ifdef LC_SUPPORT_O_COMMANDS
        LC_GCODE_TYPE_O,
#endif
        LC_GCODE_TYPE_F,
        LC_GCODE_TYPE_M,
        LC_GCODE_TYPE_G,

        LC_GCODE_TYPE_NONE,
    }; // order is important

    const char *command_ptr = line;

    for (uint8_t i = 0; lc_gcode_command_type_arr[i] != LC_GCODE_TYPE_NONE; i++)
    {
        bool command_existed = false;
        command_ptr = line;
        parsed_command.command_type = lc_gcode_command_type_arr[i];

        if (!lc_gcode_parser_get_command(&command_ptr, lc_gcode_command_type_arr[i], &command_existed, &parsed_command.command_number, &parsed_command.subcommand_existed, &parsed_command.sub_command_number))
            return false;

        while (command_existed)
        {
            switch (lc_gcode_command_type_arr[i])
            {
            case LC_GCODE_TYPE_F:
            {
                if (user_handler_cb)
                    user_handler_cb(&parsed_command);

                break;
            }
            case LC_GCODE_TYPE_G:
            {
                lc_gcode_g_command_t g_command;
                g_command.command = parsed_command;
                lc_gcode_g_command_extract_values(&g_command, line);

                if (user_handler_cb)
                    user_handler_cb(&g_command.command);

                break;
            }
            case LC_GCODE_TYPE_M:
            {
                lc_gcode_m_command_t m_command;
                m_command.command = parsed_command;
                lc_gcode_m_command_handle_attributes(&m_command, line);

                if (user_handler_cb)
                    user_handler_cb(&m_command.command);

                break;
            }
            default:
                break;
            }
            parsed_command.command_type = lc_gcode_command_type_arr[i];

            if (!lc_gcode_parser_get_command(&command_ptr, lc_gcode_command_type_arr[i], &command_existed, &parsed_command.command_number, &parsed_command.subcommand_existed, &parsed_command.sub_command_number))
                return false;
        }
    }

    return true;
}
/*********************************************************/
