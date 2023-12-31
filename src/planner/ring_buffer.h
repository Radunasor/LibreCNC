#if 0

#include "common_defs.h"
#include "gcode/gcode.h"


typedef struct _lc_planner_rb_t lc_planner_rb_t;

lc_planner_rb_t *lc_planner_rb_create(size_t size);
void lc_planner_rb_destroy(lc_planner_rb_t *rb);
bool lc_planner_rb_insert(lc_planner_rb_t *rb, lc_gcode_data_t data);
bool lc_planner_rb_remove(lc_planner_rb_t *rb, lc_gcode_data_t *data);
size_t lc_planner_rb_get_elemets_count(lc_planner_rb_t *rb);
size_t lc_planner_rb_get_size(lc_planner_rb_t *rb);
bool lc_planner_rb_is_full(lc_planner_rb_t *rb);

#endif