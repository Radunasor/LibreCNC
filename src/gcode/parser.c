#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"
#include "gcode.h"

static inline char *lc_parser_get_tag_val(const char *line, const char tag, float *value)
{
    const char *char_ptr = strchr(line, tag);

    if (!char_ptr)
        return NULL;

    if (!isdigit(*(char_ptr + 1)))
    {
        LC_LOG_ERROR("wrong Gcode format at %s. unable to parse : <%s>", line, char_ptr);
        return false;
    }

    char *end_ptr = NULL;
    *value = strtof(char_ptr + 1, &end_ptr);

    if (end_ptr == char_ptr)
        return NULL;

    return end_ptr;
}

bool lc_gcode_parser_get_value(const char *line, const char tag, float *value)
{
    if (!line || !value)
        return false;

    return lc_parser_get_tag_val(line, tag, value) != NULL;
}

static const char lc_gcode_parser_get_gcode_char_tag(lc_gcode_command_type_t command_type)
{
    char tag = 0;

    switch (command_type)
    {
    case LC_GCODE_TYPE_F:
        tag = 'F';
        break;
    case LC_GCODE_TYPE_M:
        tag = 'M';
        break;
    case LC_GCODE_TYPE_G:
        tag = 'G';
        break;
    default:
        break;
    }

    return tag;
}

bool lc_gcode_parser_get_command(const char **line, const lc_gcode_command_type_t command_type, uint32_t *command, bool *sub_command_existed, uint16_t *sub_command_value)
{
    if (line == NULL)
        return false;

    const char tag = lc_gcode_parser_get_gcode_char_tag(command_type);
    if(!tag)
        return false;

    *sub_command_existed = false;

    float command_val = 0;
    char *end_ptr = lc_parser_get_tag_val(*line, tag, &command_val);

    if (!end_ptr)
        return false;

    *command = (uint32_t)command_val;
    *sub_command_value = (uint16_t)roundf(100 * (command_val - (float)(*command)));
    *sub_command_value = *sub_command_value % 10 > 0 ? *sub_command_value : *sub_command_value / 10;
    *sub_command_existed = (*sub_command_value > 0);

    *line = end_ptr;

    return true;
}
