#ifndef GCODE_H
#define GCODE_H

#include "common_defs.h"
#include "gcode_base_obj.h"
#include "g_command.h"
#include "m_command.h"
#include "parameter.h"

typedef void (*lc_gcode_user_handler_cb_t)(const lc_gcode_obj_t *);

void lc_gcode_init();
void lc_gcode_deinit();
bool lc_gcode_get_initialized();

bool lc_gcode_set_end_of_file();
void lc_gcode_set_handler_callback(lc_gcode_user_handler_cb_t cb);

bool lc_gcode_process_line(const char *line, size_t line_num);

lc_gcode_command_type_t inline lc_gcode_get_command_type(const lc_gcode_obj_t *gcode_obj){
    LC_ASSERT(gcode_obj, "gcode obj can't be a NULL pointer!");
    return gcode_obj->command_type;
}

uint32_t inline lc_gcode_get_command_number(const lc_gcode_obj_t *gcode_obj)
{
    LC_ASSERT(gcode_obj, "gcode obj can't be a NULL pointer!");

    return gcode_obj->command_number;
}

bool inline lc_gcode_get_sub_command_existed(const lc_gcode_obj_t *gcode_obj)
{
    LC_ASSERT(gcode_obj, "gcode obj can't be a NULL pointer!");
    
    return gcode_obj->subcommand_existed;
}

uint16_t inline lc_gcode_get_sub_command_number(const lc_gcode_obj_t *gcode_obj)
{
    LC_ASSERT(gcode_obj, "gcode obj can't be a NULL pointer!");

    return gcode_obj->sub_command_number;
}

#endif