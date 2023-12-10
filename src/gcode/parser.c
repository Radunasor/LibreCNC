#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"

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

bool lc_gcode_parser_get_command(const char **line, const char tag, uint16_t *command, bool *sub_command_existed, uint16_t *sub_command_value)
{
    if (line == NULL)
        return false;

    *sub_command_existed = false;

    float command_val = 0;
    char *end_ptr = lc_parser_get_tag_val(*line, tag, &command_val);

    if (!end_ptr)
        return false;

    *command = (uint16_t)command_val;
    *sub_command_value = round(100 * (command_val - *command));
    *sub_command_value = *sub_command_value % 10 > 0 ? *sub_command_value : *sub_command_value / 10;
    *sub_command_existed = (*sub_command_value > 0);

    *line = end_ptr;

    return true;
}
