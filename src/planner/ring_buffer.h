#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "common_defs.h"
#include "stepper/stepper.h"

typedef struct lc_planner_rb_st lc_planner_rb_t;

lc_planner_rb_t *lc_planner_rb_create(size_t size);
void lc_planner_rb_destroy(lc_planner_rb_t *rb);
bool lc_planner_rb_insert(lc_planner_rb_t *rb, const lc_stepper_t *steps);
bool lc_planner_rb_remove(lc_planner_rb_t *rb, lc_stepper_t *steps);
size_t lc_planner_rb_get_elemets_count(lc_planner_rb_t *rb);
size_t lc_planner_rb_get_size(lc_planner_rb_t *rb);
bool lc_planner_rb_is_full(lc_planner_rb_t *rb);

#endif