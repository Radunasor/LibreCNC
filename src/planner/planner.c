#include <string.h>

#include "planner.h"
#include "ring_buffer.h"

static lc_planner_rb_t *rb;
static bool initialized = false;

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static void lc_planner_gcode_parser_callback(const lc_gcode_obj_t *parsed_gcode);
/******************************************************/

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

void lc_planner_plan()
{
}

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static void lc_planner_gcode_parser_callback(const lc_gcode_obj_t *parsed_gcode)
{
    switch (parsed_gcode->command_type)
    {
    case LC_GCODE_TYPE_G:
    {
        lc_stepper_t *steps = NULL;
        // todo: ask motion control module to calculate steps and dir bit
        lc_planner_rb_insert(rb, steps);
    }
    break;
    case LC_GCODE_TYPE_M:
        break;
    case LC_GCODE_TYPE_F:
        break;
    default:
        break;
    }
}
/*********************************************************/