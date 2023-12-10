#ifndef PARSER_H
#define PARSER_H

#include "gcode.h"

bool lc_gcode_parser_get_value(const char *line, const char tag, float *value);
bool lc_gcode_parser_get_command(const char **line, const char tag, uint16_t *command, bool *sub_command_existed, uint16_t *sub_command_value);
#endif