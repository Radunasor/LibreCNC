#include <string.h>

#include "planner.h"
#include "ring_buffer.h"

static lc_planner_rb_t *rb;
static bool initialized = false;

void lc_planner_init()
{
    if (initialized)
        return;

    rb = lc_planner_rb_create(LC_PLANNER_OBJ_RING_BUFFER_SIZE);

    initialized = true;
}

void lc_planner_deinit()
{
    if (!initialized)
        return;

    lc_planner_rb_destroy(rb);
    rb = NULL;

    initialized = false;
}

bool lc_planner_get_initialized()
{
    return initialized;
}

static void lc_planner_produce_new_gcode_obj()
{
    // lc_gcode_get_new_object();
}