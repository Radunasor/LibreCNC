#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"

bool lc_gcode_parser_get_value(const char *line, const char tag, float *value)
{
    if (!line || !value)
        return false;

    const char *char_ptr = strchr(line, tag);

    if (!char_ptr)
        return false;

    if (!isdigit(*(char_ptr + 1)))
    {
        LC_LOG_ERROR("wrong Gcode format at %s. unable to parse : <%s>", line, char_ptr);
        return false;
    }

    char *end_ptr = NULL;
    *value = strtof(char_ptr + 1, &end_ptr);

    if (end_ptr == char_ptr)
        return false;

    return true;
}

bool lc_gcode_parser_get_command(const char *line, const char tag, uint16_t *command, bool *sub_command_existed, uint16_t *sub_command_value)
{
    if (line == NULL)
        return false;

    *sub_command_existed = false;

    float command_val = 0;
    if (!lc_gcode_parser_get_value(line, tag, &command_val))
        return false;

    *command = (uint16_t)command_val;
    *sub_command_value = round(100 * (command_val - *command));
    *sub_command_value = *sub_command_value % 10 > 0 ? *sub_command_value : *sub_command_value / 10;
    *sub_command_existed = (*sub_command_value > 0);

    return true;
}
