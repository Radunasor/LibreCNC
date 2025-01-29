#ifndef G_COMMANDS_H
#define G_COMMANDS_H

#include "common_defs.h"
#include "gcode/gcode.h"

typedef enum
{
    LC_PLANNER_GCODE_LIST_G0 = 0,
    LC_PLANNER_GCODE_LIST_G1,

    _LC_PLANNER_GCODE_LIST_LAST,
} lc_planner_gcode_list_t;

void lc_planner_on_G_command(const lc_gcode_obj_t *parsed_code);

#endif