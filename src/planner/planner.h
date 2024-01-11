#ifndef PLANNER_H
#define PLANNER_H

#define LC_PLANNER_OBJ_RING_BUFFER_SIZE 32

#include "common_defs.h"
#include "gcode/gcode.h"

void lc_planner_init();
void lc_planner_deinit();
bool lc_planner_get_initialized();
void lc_planner_plan();

#endif