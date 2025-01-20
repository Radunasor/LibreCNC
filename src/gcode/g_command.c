#include <string.h>

#include "g_command.h"
#include "parser.h"
#include "logger/logger.h"

static lc_gcode_g_command_hanler_cb_t handler_cb = NULL;

bool lc_gcode_g_command_extract_values(lc_gcode_obj_t *command, const char *line)
{
    lc_gcode_g_command_t *g_command = (lc_gcode_g_command_t *) command;

    // memset(command + (sizeof(lc_gcode_obj_t)), 0, sizeof(lc_gcode_g_command_t) - sizeof(lc_gcode_obj_t));

    struct lc_gcode_parse_tag_map
    {
        const char tag;
        lc_gcode_g_command_attr_t *attr;
    } lc_gcode_parser_tag_map[] = {
        {'X', &g_command->X},
        {'Y', &g_command->Y},
        {'Z', &g_command->Z},
        {'I', &g_command->I},
        {'J', &g_command->J},
        {'K', &g_command->K},
        {'L', &g_command->L},
        {'N', &g_command->N},
        {'P', &g_command->P},
        {'R', &g_command->R},
        {'S', &g_command->S},
        {'T', &g_command->T},

        {'\0', NULL},
    };

    for (uint8_t i = 0; lc_gcode_parser_tag_map[i].tag; i++)
        if (!lc_gcode_parser_get_value(line, lc_gcode_parser_tag_map[i].tag, &(lc_gcode_parser_tag_map[i].attr->existed), &(lc_gcode_parser_tag_map[i].attr->value)))
            return false;

    if(handler_cb)
        handler_cb(command);
    else
        LC_LOG_WARN("GCODE G COMMAND CALLBACK HANDLER HAS NOT SET!");

    return true;
}

void lc_gcode_g_command_set_handler_callback(lc_gcode_g_command_hanler_cb_t callback)
{
    handler_cb = callback;
}