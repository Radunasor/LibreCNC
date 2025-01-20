#include <string.h>

#include "m_command.h"
#include "parser.h"
#include "logger/logger.h"

static lc_gcode_m_command_hanler_cb_t handler_cb = NULL;

bool lc_gcode_m_command_extract_attributes(lc_gcode_obj_t *command, const char *line)
{
    lc_gcode_m_command_t *m_command = (lc_gcode_m_command_t *)command;

    struct lc_gcode_parse_tag_map
    {
        const char tag;
        lc_gcode_m_command_attr_t *attr;
    } lc_gcode_parser_tag_map[] = {
        {'R', &m_command->R},
        {'Q', &m_command->Q},
        {'P', &m_command->P},
        {'E', &m_command->E},
        {'L', &m_command->L},

        {'\0', NULL},
    };

    for (uint8_t i = 0; lc_gcode_parser_tag_map[i].tag; i++)
        if (!lc_gcode_parser_get_value(line, lc_gcode_parser_tag_map[i].tag, &(lc_gcode_parser_tag_map[i].attr->existed), &(lc_gcode_parser_tag_map[i].attr->value)))
            return false;

    if (handler_cb)
        handler_cb(command);
    else
        LC_LOG_WARN("GCODE M COMMAND CALLBACK HANDLER HAS NOT SET!");

    return true;
}

void lc_gcode_m_command_set_handler_callback(lc_gcode_m_command_hanler_cb_t callback)
{
    handler_cb = callback;
}