#include <string.h>

#include "planner.h"
#include "ring_buffer.h"

static lc_planner_rb_t *rb;
static bool initialized = false;

/*****************************************************/
/***********static functions defenitions**************/
/*****************************************************/
static void lc_planner_gcode_parser_callback(const lc_gcode_obj_t *parsed_gcode);
/*****************************************************/

void lc_planner_init()
{
    if (initialized)
        return;

    rb = lc_planner_rb_create(LC_PLANNER_OBJ_RING_BUFFER_SIZE);

    lc_gcode_set_parse_callback(lc_planner_gcode_parser_callback);

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

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static void lc_planner_gcode_parser_callback(const lc_gcode_obj_t *parsed_gcode)
{
    lc_planner_rb_insert(rb, parsed_gcode);
}
/*********************************************************/