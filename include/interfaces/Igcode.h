#ifndef IGCODE_H
#define IGCODE_H

#include "common_defs.h"

typedef struct
{
    bool (*lc_interface_gcode_init)();
    bool (*lc_interface_gcode_deinit)();

    bool (*lc_interface_gcode_get_line)(const char *line, size_t *line_number);
} lc_interface_gcode_t;

#endif