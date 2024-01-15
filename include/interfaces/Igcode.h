#ifndef IGCODE_H
#define IGCODE_H

#include "common_defs.h"

typedef struct
{
    bool (*lc_interface_gcode_init)();
    bool (*lc_interface_gcode_deinit)();

    bool (*lc_interface_gcode_get_line)(char *line, size_t *line_number);
    bool (*lc_interface_gcode_get_end_of_file)();
} lc_interface_gcode_t;

#endif