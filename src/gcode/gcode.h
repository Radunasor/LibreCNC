#ifndef GCODE_H
#define GCODE_H

#include "common_defs.h"
#include "interfaces/Igcode.h"

typedef struct
{
    bool existed;
    float value;
} lc_gcode_attr_t;

typedef struct
{
    lc_gcode_attr_t X;
    lc_gcode_attr_t Y;
    lc_gcode_attr_t Z;
    lc_gcode_attr_t I;
    lc_gcode_attr_t J;
    lc_gcode_attr_t K;
    lc_gcode_attr_t L;
    lc_gcode_attr_t N;
    lc_gcode_attr_t P;
    lc_gcode_attr_t R;
    lc_gcode_attr_t S;
    lc_gcode_attr_t T;
} lc_gcode_attrbute_value_t;

typedef enum
{
    LC_GCODE_TYPE_G,
    LC_GCODE_TYPE_M,
    LC_GCODE_TYPE_F,

    _LC_GCODE_TYPE_LAST,
} lc_gcode_code_type_t;

typedef void (*lc_gcode_cb_t)(const uint16_t command, const bool sub_command_existed, const uint16_t sub_command, const lc_gcode_attrbute_value_t *values);

void lc_gcode_init(lc_interface_gcode_t *gcode_cbs);
void lc_gcode_deinit();
bool lc_gcode_get_initialized();

void lc_gcode_set_callback(lc_gcode_code_type_t type, lc_gcode_cb_t cb);
bool lc_gcode_process_line();
#endif