#include <string.h>

#include "g_command.h"
#include "parser.h"
#include "logger/logger.h"

bool lc_gcode_g_command_extract_values(lc_gcode_g_command_t *g_command, const char *line)
{
    struct lc_gcode_parse_tag_map
    {
        const char tag;
        lc_gcode_command_attr_t *attr;
    } lc_gcode_parser_tag_map[] = {
#define LC_GCODE_G_COMMAND_FIELD(attr) {#attr[0], &g_command->attr},
        LC_GCODE_G_COMMAND_SUPPORTED_FIELDS
#undef LC_GCODE_G_COMMAND_FIELD

        {'\0', NULL},
    };

    for (uint8_t i = 0; lc_gcode_parser_tag_map[i].tag; i++)
        if (!lc_gcode_parser_get_value(line, lc_gcode_parser_tag_map[i].tag, &(lc_gcode_parser_tag_map[i].attr->existed), &(lc_gcode_parser_tag_map[i].attr->value)))
            return false;

    return true;
}
