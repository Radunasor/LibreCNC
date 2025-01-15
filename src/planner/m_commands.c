#include "m_commands.h"

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static void lc_planner_m_command_m0(const lc_gcode_obj_t *parsed_code);
static void lc_planner_m_command_m1(const lc_gcode_obj_t *parsed_code);
/******************************************************/

struct m_commands_handlers_st
{
    lc_planner_mcode_list_t code;
    void (*handler_func)();
}m_commands_handlers[] = {
    {LC_PLANNER_MCODE_LIST_M0, lc_planner_m_command_m0},
    {LC_PLANNER_MCODE_LIST_M1, lc_planner_m_command_m1},

    {_LC_PLANNER_MCODE_LIST_LAST, NULL},
};

void lc_planner_on_M_command(const lc_gcode_obj_t *parsed_code)
{
    uint8_t handler_index = 0;
    while(m_commands_handlers[handler_index].code != _LC_PLANNER_MCODE_LIST_LAST)
    {
        if (m_commands_handlers[handler_index].code == (lc_planner_mcode_list_t)parsed_code->command_number)
            {
                if(m_commands_handlers[handler_index].handler_func)
                    m_commands_handlers[handler_index].handler_func(parsed_code);
                
                break;
            }
        handler_index++;
    }
}

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static void lc_planner_m_command_m0(const lc_gcode_obj_t *parsed_code)
{

}

static void lc_planner_m_command_m1(const lc_gcode_obj_t *parsed_code)
{

}
/*********************************************************/