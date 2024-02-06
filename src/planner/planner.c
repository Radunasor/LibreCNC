#include <string.h>

#include "planner.h"
#include "ring_buffer.h"

static lc_planner_rb_t *rb;
static bool initialized = false;

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static void lc_planner_gcode_parser_callback(const lc_gcode_obj_t *parsed_gcode);
static void lc_planner_on_G_command(const lc_gcode_obj_t *parsed_gcode);
static void lc_planner_on_M_command(const lc_gcode_obj_t *parsed_gcode);
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
    static lc_stepper_t steps;

    switch (parsed_gcode->command_type)
    {
    case LC_GCODE_TYPE_G:
        lc_planner_on_G_command(parsed_gcode);
    break;
    case LC_GCODE_TYPE_M:
        lc_planner_on_M_command(parsed_gcode);
        break;
    case LC_GCODE_TYPE_F:
        // todo: change the feedrate
        break;
    default:
        break;
    }
}

static void lc_planner_on_G_command(const lc_gcode_obj_t *parsed_gcode)
{
        lc_stepper_t *steps = NULL;

        switch (parsed_gcode->command_number)
        {
        case 0: //G0
        case 1: //G1
            // todo: ask motion control module to calculate steps and dir bit
            lc_planner_rb_insert(rb, steps);
            break;
        default:
            break;
        }
}

static void lc_planner_on_M_command(const lc_gcode_obj_t *parsed_gcode)
{
    switch (parsed_gcode->command_number)
    {
    case 0: //M0
    case 1: //M1
        // todo: change the required machine configs
        break;
    default:
        break;
    }
}
/*********************************************************/