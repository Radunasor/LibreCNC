#include <string.h>

#include "planner.h"
#include "ring_buffer.h"
#include "g_commands.h"
#include "m_commands.h"

static lc_planner_rb_t *rb;
static bool initialized = false;

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static void lc_planner_handle_gcode(const lc_gcode_obj_t *parsed_gcode);
/******************************************************/

void lc_planner_init()
{
    if (initialized)
        return;

    rb = lc_planner_rb_create(LC_PLANNER_OBJ_RING_BUFFER_SIZE);
    lc_gcode_set_parse_cb(lc_planner_gcode_parser_callback);

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

void lc_planner_gcode_parser_callback(const lc_gcode_obj_t *parsed_gcode)
{
    // todo: need to handle the ring buffer
}

void lc_planner_plan()
{
    if (lc_planner_rb_get_elemets_count(rb) > 0)
    {
        lc_gcode_obj_t *gcode_obj = NULL;
        lc_planner_rb_remove(rb, gcode_obj);

        lc_planner_handle_gcode(gcode_obj);

        return;
    }

    while (!lc_planner_rb_is_full(rb) /* || !get_end_of_file()*/) // todo: add the end of file interface
    {
        char line[8] = {0};
        size_t line_num = 0;
        // todo: get the line/line line from gcode stream
        lc_gcode_process_line(line, line_num);
    }
}

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static void lc_planner_handle_gcode(const lc_gcode_obj_t *parsed_gcode)
{
    if (!parsed_gcode)
        return;

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
/*********************************************************/