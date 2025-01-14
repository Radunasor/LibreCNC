#ifndef PLANNER_H
#define PLANNER_H

#include "common_defs.h"
#include "gcode/gcode.h"

#define LC_PLANNER_OBJ_RING_BUFFER_SIZE 32

void lc_planner_init();
void lc_planner_deinit();
bool lc_planner_get_initialized();
void lc_planner_plan();
void lc_planner_gcode_parser_callback(const lc_gcode_obj_t *parsed_gcode);

#endif