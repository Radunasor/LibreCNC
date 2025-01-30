#ifndef PARAMETER_H
#define PARAMETER_H

#include "common_defs.h"

#if LC_GCODE_PARAMETER_SUPPORT

#define LC_GCODE_PARAMETER_MAX_NAME_LENTGH 64
#define LC_GCODE_PARAMETER_SCOPE_GLOBAL 0
#define LC_GCODE_PARAMETER_SCOPE_DEPTH 4

#define LC_GCODE_PARAMETER_USER_RANGE_BEGIN 31
#define LC_GCODE_PARAMETER_USER_RANGE_END 5000

typedef enum
{
    LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS,
    LC_GCODE_PARAMETERS_RES_TYPE_SYSTEM_PARAM,
    LC_GCODE_PARAMETERS_RES_TYPE_RESERVED_PARAM,

    LC_GCODE_PARAMETERS_RES_TYPE_NONE,
} lc_gcode_parameter_res_type_t;

void lc_gcode_parameter_init();
void lc_gcode_parameter_deinit();
bool lc_gcode_parameter_get_initialized();

lc_gcode_parameter_res_type_t lc_gcode_parameter_named_set(const char *name, float value);
bool lc_gcode_parameter_named_get(const char *name, float *value);

lc_gcode_parameter_res_type_t lc_gcode_parameter_numeric_set(uint16_t id, float value);
bool lc_gcode_parameter_numeric_get(uint16_t id, float *value);

bool lc_gcode_paramater_scope_push(uint16_t scope);
uint16_t lc_gcode_paramater_scope_pop();
uint16_t lc_gcode_paramater_get_current_scope();
uint8_t lc_gcode_paramater_get_current_scope_depth();

#endif

#endif