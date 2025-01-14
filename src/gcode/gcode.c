#include <string.h>

#include "gcode.h"
#include "parser.h"

#define CHECK_INITIALIIZED LC_ASSERT(initialized, "GCODE module not initialized!");

static bool initialized = false;
static lc_gcode_parse_cb_t parse_cb = NULL;

static lc_gcode_obj_t gcode_obj = {
    .command_number = 0,
    .command_type = LC_GCODE_TYPE_NONE,
    .command_values = NULL,
    .subcommand_existed = false,
    .sub_command_number = 0,
};

static lc_gcode_attrbute_value_t line_gcode_attributes =
    {
        .X = {false, 0},
        .Y = {false, 0},
        .Z = {false, 0},
        .I = {false, 0},
        .J = {false, 0},
        .K = {false, 0},
        .L = {false, 0},
        .N = {false, 0},
        .P = {false, 0},
        .R = {false, 0},
        .S = {false, 0},
        .T = {false, 0},
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

    memset(&line_gcode_attributes, 0, sizeof(lc_gcode_attrbute_value_t));
    parse_cb = NULL;
    initialized = false;
}

bool lc_gcode_get_initialized()
{
    return initialized;
}

void lc_gcode_set_parse_cb(lc_gcode_parse_cb_t parse_callback)
{
    if (!parse_callback)
        return;

    parse_cb = parse_callback;
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

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static bool lc_gcode_parse_line(char *line, size_t line_num)
{
    lc_gcode_parser_mark_comments(line);

    struct lc_gcode_parse_tag_map
    {
        const char tag;
        lc_gcode_attr_t *attr;
    } lc_gcode_parser_tag_map[] = {
        {'X', &line_gcode_attributes.X},
        {'Y', &line_gcode_attributes.Y},
        {'Z', &line_gcode_attributes.Z},
        {'I', &line_gcode_attributes.I},
        {'J', &line_gcode_attributes.J},
        {'K', &line_gcode_attributes.K},
        {'L', &line_gcode_attributes.L},
        {'N', &line_gcode_attributes.N},
        {'P', &line_gcode_attributes.P},
        {'R', &line_gcode_attributes.R},
        {'S', &line_gcode_attributes.S},
        {'T', &line_gcode_attributes.T},

        {'\0', NULL},
    };

    for (uint8_t i = 0; lc_gcode_parser_tag_map[i].tag; i++)
        if (!lc_gcode_parser_get_value(line, lc_gcode_parser_tag_map[i].tag, &(lc_gcode_parser_tag_map[i].attr->existed), &(lc_gcode_parser_tag_map[i].attr->value)))
        {
            LC_LOG_ERROR("ERROR on GCODE Line %d", line_num);
            return false;
        }

    lc_gcode_command_type_t lc_gcode_command_type_arr[] = {
        LC_GCODE_TYPE_F,
        LC_GCODE_TYPE_M,
        LC_GCODE_TYPE_G,

        LC_GCODE_TYPE_LAST,
    }; // order is important

    const char *command_ptr = line;

    for (uint8_t i = 0; lc_gcode_command_type_arr[i] != LC_GCODE_TYPE_LAST; i++)
    {
        bool command_existed = false;
        command_ptr = line;

        if (!lc_gcode_parser_get_command(&command_ptr, lc_gcode_command_type_arr[i], &command_existed, &gcode_obj.command_number, &gcode_obj.subcommand_existed, &gcode_obj.sub_command_number))
            return false;

        while (command_existed)
        {
            gcode_obj.command_type = lc_gcode_command_type_arr[i];
            gcode_obj.command_values = line_gcode_attributes;

            if (parse_cb)
                parse_cb(&gcode_obj);
            else
                LC_LOG_WARN("GCODE parsing callback has to be set to get the parsed result from the module");

            if (!lc_gcode_parser_get_command(&command_ptr, lc_gcode_command_type_arr[i], &command_existed, &gcode_obj.command_number, &gcode_obj.subcommand_existed, &gcode_obj.sub_command_number))
                return false;
        }
    }

    return true;
}
/*********************************************************/
