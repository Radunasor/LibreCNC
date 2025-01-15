#include "g_commands.h"

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static void lc_planner_g_command_g0(const lc_gcode_obj_t *parsed_code);
static void lc_planner_g_command_g1(const lc_gcode_obj_t *parsed_code);
/******************************************************/

struct g_commands_handlers_st
{
    lc_planner_gcode_list_t code;
    void (*handler_func)(const lc_gcode_obj_t *);
}g_commands_handlers[] = {
    {LC_PLANNER_GCODE_LIST_G0, lc_planner_g_command_g0},
    {LC_PLANNER_GCODE_LIST_G1, lc_planner_g_command_g1},

    {_LC_PLANNER_GCODE_LIST_LAST, NULL},
};

void lc_planner_on_G_command(const lc_gcode_obj_t *parsed_code)
{
    uint8_t handler_index = 0;
    while(g_commands_handlers[handler_index].code != _LC_PLANNER_GCODE_LIST_LAST)
    {
        if (g_commands_handlers[handler_index].code == (lc_planner_gcode_list_t)parsed_code->command_number)
            {
                if(g_commands_handlers[handler_index].handler_func)
                    g_commands_handlers[handler_index].handler_func(parsed_code);
                
                break;
            }
        handler_index++;
    }
}

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static void lc_planner_g_command_g0(const lc_gcode_obj_t *parsed_code)
{

}

static void lc_planner_g_command_g1(const lc_gcode_obj_t *parsed_code)
{

}
/*********************************************************/