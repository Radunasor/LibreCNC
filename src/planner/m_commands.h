#ifndef M_COMMANDS_H
#define M_COMMANDS_H

#include "common_defs.h"
#include "gcode/gcode.h"

typedef enum {
    LC_PLANNER_MCODE_LIST_M0 = 0,
    LC_PLANNER_MCODE_LIST_M1,

    _LC_PLANNER_MCODE_LIST_LAST,
}lc_planner_mcode_list_t;

void lc_planner_on_M_command(const lc_gcode_obj_t *parsed_code);

#endif
