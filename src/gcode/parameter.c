#include "parameter.h"

#if LC_GCODE_PARAMETER_SUPPORT

#include "config/config.h"

static bool initialized = false;

static inline lc_gcode_parameter_res_type_t check_parameter_range(uint16_t id)
{
    lc_gcode_parameter_res_type_t res = LC_GCODE_PARAMETERS_RES_TYPE_NONE;
    switch (id)
    {
    case LC_GCODE_PARAMETER_USER_RANGE_BEGIN ... LC_GCODE_PARAMETER_USER_RANGE_END:
        res = LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS;
        break;
    default:
        break;
    }
}

void lc_gcode_parameter_init()
{
    if(!lc_config_get_initialized() || initialized)
        return;
    
    initialized = true;
}

void lc_gcode_parameter_deinit()
{
    if(!initialized)
        return;
    
    initialized = false;
}

bool lc_gcode_parameter_get_initialized()
{
    return initialized;
}

lc_gcode_parameter_res_type_t lc_gcode_parameter_named_set(const char *name, float value)
{
    CHECK_INITIALIIZED

    lc_config_set_float(LC_CONFIG_KEY_STRING(name), value);

    return LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS;
}

bool lc_gcode_parameter_named_get(const char *name, float *value)
{
    CHECK_INITIALIIZED
}

lc_gcode_parameter_res_type_t lc_gcode_parameter_numeric_set(int id, float value)
{
    CHECK_INITIALIIZED

    lc_gcode_parameter_res_type_t range_ckeck = check_parameter_range(id);
    if(range_ckeck != LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS)
        return range_ckeck;

    lc_config_set_float(LC_CONFIG_KEY_INT(&id), value);

    return LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS;
}

bool lc_gcode_parameter_numeric_get(uint16_t id, float *value)
{
    CHECK_INITIALIIZED
}

#endif
