#include "parameter.h"

#if LC_GCODE_PARAMETER_SUPPORT

#include "data_structures/map/map.h"
#include <string.h>

typedef struct
{
    lc_map_t *var_map;
    uint16_t scope;
} lc_gcode_parameter_scope_t;

struct lc_gcode_parameter_scope_stack_st
{
    lc_gcode_parameter_scope_t stack[LC_GCODE_PARAMETER_SCOPE_DEPTH];
    uint8_t top;
} scope_stack;

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

    return res;
}

void lc_gcode_parameter_init()
{
    initialized = true;

    lc_gcode_paramater_scope_push(LC_GCODE_PARAMETER_SCOPE_GLOBAL);
}

void lc_gcode_parameter_deinit()
{
    if (!initialized)
        return;

    for (uint8_t i = 0; i < LC_GCODE_PARAMETER_SCOPE_DEPTH; i++)
    {
        if (scope_stack.stack[i].var_map)
            lc_map_destroy(scope_stack.stack[i].var_map);

        scope_stack.stack[i].var_map = NULL;
        scope_stack.stack[i].scope = 0;
    }

    scope_stack.top = 0;
    initialized = false;
}

bool lc_gcode_parameter_get_initialized()
{
    return initialized;
}

lc_gcode_parameter_res_type_t lc_gcode_parameter_named_set(const char *name, float value)
{
    CHECK_INITIALIIZED

    lc_map_insert(scope_stack.stack[scope_stack.top - 1].var_map, name, MIN(strlen(name), LC_GCODE_PARAMETER_MAX_NAME_LENTGH), (void *)&value, sizeof(float));

    return LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS;
}

bool lc_gcode_parameter_named_get(const char *name, float *value)
{
    CHECK_INITIALIIZED

    float *tmp_val = NULL;
    bool res = false;

    for (uint8_t depth = scope_stack.top; depth > 0; depth--)
    {
        size_t output_size = 0;
        res = lc_map_find(scope_stack.stack[depth - 1].var_map, name, MIN(strlen(name), LC_GCODE_PARAMETER_MAX_NAME_LENTGH), (void **)&tmp_val, &output_size);
        if (res)
        {
            *value = *tmp_val;
            break;
        }
    }

    return res;
}

lc_gcode_parameter_res_type_t lc_gcode_parameter_numeric_set(uint16_t id, float value)
{
    CHECK_INITIALIIZED

    lc_gcode_parameter_res_type_t range_ckeck = check_parameter_range(id);
    if (range_ckeck != LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS)
        return range_ckeck;

    lc_map_insert(scope_stack.stack[scope_stack.top - 1].var_map, &id, sizeof(uint16_t), (void *)&value, sizeof(float));

    return LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS;
}

bool lc_gcode_parameter_numeric_get(uint16_t id, float *value)
{
    CHECK_INITIALIIZED

    float *tmp_val = NULL;
    bool res = false;

    for (uint8_t depth = scope_stack.top; depth > 0; depth--)
    {
        size_t output_size = 0;
        res = lc_map_find(scope_stack.stack[depth - 1].var_map, &id, sizeof(uint16_t), (void **)&tmp_val, &output_size);
        if (res)
        {
            *value = *tmp_val;
            break;
        }
    }

    return res;
}

bool lc_gcode_paramater_scope_push(uint16_t scope)
{
    CHECK_INITIALIIZED

    if (scope_stack.top >= LC_GCODE_PARAMETER_SCOPE_DEPTH) // Stack overflow check
        return false;

    scope_stack.stack[scope_stack.top].var_map = lc_map_create();
    scope_stack.stack[scope_stack.top].scope = scope;

    scope_stack.top++; // Increment top after assignment

    return true;
}

uint16_t lc_gcode_paramater_scope_pop()
{
    CHECK_INITIALIIZED

    if (scope_stack.top == 0) // Stack underflow check
        return 0;

    uint16_t tmp_scope = scope_stack.stack[scope_stack.top - 1].scope;

    if (tmp_scope == LC_GCODE_PARAMETER_SCOPE_GLOBAL) // Never pop the main scope
        return 0;

    scope_stack.top--; // Decrement first before accessing

    lc_map_destroy(scope_stack.stack[scope_stack.top].var_map);
    scope_stack.stack[scope_stack.top].var_map = NULL;
    scope_stack.stack[scope_stack.top].scope = 0;

    return tmp_scope;
}

uint16_t lc_gcode_paramater_get_current_scope()
{
    CHECK_INITIALIIZED

    return scope_stack.stack[scope_stack.top - 1].scope;
}

uint8_t lc_gcode_paramater_get_current_scope_depth()
{
    CHECK_INITIALIIZED

    return scope_stack.top;
}

#endif
