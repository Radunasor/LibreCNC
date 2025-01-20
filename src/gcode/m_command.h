#ifndef M_COMMAND_H
#define M_COMMAND_H

#include "common_defs.h"
#include "gcode_base_obj.h"

#define LC_GCODE_M_COMMAND_ATTR_GETTER(ATTR) \
            bool inline lc_gcode_m_command_get_attr_##ATTR(lc_gcode_obj_t *command, float *value) \
            {                                                                                     \
                lc_gcode_m_command_t *m_command = (lc_gcode_m_command_t *) command;               \
                LC_ASSERT(command, "gcode obj can't be a NULL pointer!");                         \
                *value = m_command->ATTR.value;                                                   \
                return m_command->ATTR.existed;                                                   \
            };

typedef struct lc_gcode_m_command_st lc_gcode_m_command_t;
typedef void (*lc_gcode_m_command_hanler_cb_t)(const lc_gcode_obj_t *);

typedef struct lc_gcode_m_command_attr_st
{
    bool existed;
    float value;
} lc_gcode_m_command_attr_t;

struct lc_gcode_m_command_st
{
    lc_gcode_obj_t command;
    lc_gcode_m_command_attr_t R;
    lc_gcode_m_command_attr_t Q;
    lc_gcode_m_command_attr_t P;
    lc_gcode_m_command_attr_t E;
    lc_gcode_m_command_attr_t L;
};

LC_GCODE_M_COMMAND_ATTR_GETTER(R);
LC_GCODE_M_COMMAND_ATTR_GETTER(Q);
LC_GCODE_M_COMMAND_ATTR_GETTER(P);
LC_GCODE_M_COMMAND_ATTR_GETTER(E);
LC_GCODE_M_COMMAND_ATTR_GETTER(L);

bool lc_gcode_m_command_extract_attributes(lc_gcode_obj_t *command, const char *line);
void lc_gcode_m_command_set_handler_callback(lc_gcode_m_command_hanler_cb_t callback);

#endif