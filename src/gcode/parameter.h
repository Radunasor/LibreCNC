#ifndef PARAMETER_H
#define PARAMETER_H

#include "common_defs.h"

#if LC_GCODE_PARAMETER_SUPPORT

#define LC_GCODE_PARAMETER_USER_RANGE_BEGIN 31
#define LC_GCODE_PARAMETER_USER_RANGE_END   5000

typedef enum {
    LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS,
    LC_GCODE_PARAMETERS_RES_TYPE_SYSTEM_PARAM,
    LC_GCODE_PARAMETERS_RES_TYPE_RESERVED_PARAM,
    
    LC_GCODE_PARAMETERS_RES_TYPE_NONE,
}lc_gcode_parameter_res_type_t;

void lc_gcode_parameter_init();
void lc_gcode_parameter_deinit();
bool lc_gcode_parameter_get_initialized();

lc_gcode_parameter_res_type_t lc_gcode_parameter_named_set(const char *name, float value);
bool lc_gcode_parameter_named_get(const char *name, float *value);

lc_gcode_parameter_res_type_t lc_gcode_parameter_numeric_set(uint16_t id, float value);
bool lc_gcode_parameter_numeric_get(uint16_t id, float *value);

#endif

#endif