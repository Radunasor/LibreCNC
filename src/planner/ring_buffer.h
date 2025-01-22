#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "common_defs.h"
#include "gcode/gcode.h"

#define LC_PLANNER_GCODE_RB_BUFFER_SIZE 20

typedef union lc_planner_rb_buffer_gcode_union_t
{
    lc_gcode_obj_t fcommand_gcode_obj;
    lc_gcode_g_command_t gcommand_gcode_obj;
    lc_gcode_m_command_t mcommand_gcode_obj;
}lc_planner_rb_buffer_gcode_t;

typedef struct lc_planner_rb_st lc_planner_rb_t;

lc_planner_rb_t *lc_planner_rb_create();
void lc_planner_rb_destroy(lc_planner_rb_t *rb);
bool lc_planner_rb_insert(lc_planner_rb_t *rb, const lc_gcode_obj_t *plan);
bool lc_planner_rb_remove(lc_planner_rb_t *rb, lc_gcode_obj_t *plan);
size_t lc_planner_rb_get_elemets_count(lc_planner_rb_t *rb);
size_t lc_planner_rb_get_size(lc_planner_rb_t *rb);
bool lc_planner_rb_is_full(lc_planner_rb_t *rb);

#endif