#ifndef PARSER_H
#define PARSER_H

#include "gcode.h"

void lc_gcode_parser_mark_comments(char *line);
bool lc_gcode_parser_get_value(const char *line, const char tag, bool *existed, float *value);
bool lc_gcode_parser_get_command(const char **line,
                                 const lc_gcode_command_type_t command_type,
                                 bool *command_existed,
                                 uint32_t *command,
                                 bool *sub_command_existed,
                                 uint16_t *sub_command_value);
#endif