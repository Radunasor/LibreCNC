#ifndef GCODE_OBJ_H
#define GCODE_OBJ_H

#include "common_defs.h"

#define LC_GCODE_MAX_LINE_LENTGH 256

typedef enum lc_gcode_command_type_st
{
    LC_GCODE_TYPE_NONE = 0,
    LC_GCODE_TYPE_O = 'O',
    LC_GCODE_TYPE_G = 'G',
    LC_GCODE_TYPE_M = 'M',
    LC_GCODE_TYPE_F = 'F',
} lc_gcode_command_type_t;

typedef struct lc_gcode_obj_st
{
    lc_gcode_command_type_t command_type;
    uint32_t command_number;
    bool subcommand_existed;
    uint16_t sub_command_number;
}lc_gcode_obj_t;

#endif