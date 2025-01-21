#include <string.h>

#include "m_command.h"
#include "parser.h"
#include "logger/logger.h"

static lc_gcode_m_command_hanler_cb_t handler_cb = NULL;

bool lc_gcode_m_command_handle_attributes(lc_gcode_m_command_t *m_command, const char *line)
{
    struct lc_gcode_parse_tag_map
    {
        const char tag;
        lc_gcode_m_command_attr_t *attr;
    } lc_gcode_parser_tag_map[] = {
        #define LC_GCODE_M_COMMAND_FIELD(attr) {#attr[0],  &m_command->attr},
        LC_GCODE_M_COMMAND_SUPPORTED_FIELDS 
        #undef LC_GCODE_M_COMMAND_FIELD

        {'\0', NULL},
    };

    for (uint8_t i = 0; lc_gcode_parser_tag_map[i].tag; i++)
        if (!lc_gcode_parser_get_value(line, lc_gcode_parser_tag_map[i].tag, &(lc_gcode_parser_tag_map[i].attr->existed), &(lc_gcode_parser_tag_map[i].attr->value)))
            return false;

    if (handler_cb)
        handler_cb(&m_command->command);
    else
        LC_LOG_WARN("GCODE M COMMAND CALLBACK HANDLER HAS NOT SET!");

    return true;
}

void lc_gcode_m_command_set_handler_callback(lc_gcode_m_command_hanler_cb_t callback)
{
    handler_cb = callback;
}