#ifndef M_COMMAND_H
#define M_COMMAND_H

#include "common_defs.h"
#include "gcode_base_obj.h"
#include "utils.h"

#define LC_GCODE_M_COMMAND_ATTR_GETTER(ATTR) \
            bool inline lc_gcode_m_command_get_attr_##ATTR(lc_gcode_obj_t *command, float *value) \
            {                                                                                     \
                lc_gcode_m_command_t *m_command = (lc_gcode_m_command_t *) command;               \
                LC_ASSERT(command, "gcode obj can't be a NULL pointer!");                         \
                *value = m_command->ATTR.value;                                                   \
                return m_command->ATTR.existed;                                                   \
            };

typedef struct lc_gcode_m_command_st lc_gcode_m_command_t;

#define LC_GCODE_M_COMMAND_SUPPORTED_FIELDS \
    LC_GCODE_M_COMMAND_FIELD(R) \
    LC_GCODE_M_COMMAND_FIELD(Q) \
    LC_GCODE_M_COMMAND_FIELD(P) \
    LC_GCODE_M_COMMAND_FIELD(E) \
    LC_GCODE_M_COMMAND_FIELD(L) \

struct lc_gcode_m_command_st
{
    lc_gcode_obj_t command;
    #define LC_GCODE_M_COMMAND_FIELD(attr) lc_gcode_command_attr_t attr;
    LC_GCODE_M_COMMAND_SUPPORTED_FIELDS
    #undef LC_GCODE_M_COMMAND_FIELD
};

// will add accessor func named lc_gcode_g_command_get_attr_X/Y/Z...()
#define LC_GCODE_M_COMMAND_FIELD(attr) LC_GCODE_COMMAND_ATTR_ACCESSOR_GENERATOR(m, lc_gcode_m_command_t, attr)
LC_GCODE_M_COMMAND_SUPPORTED_FIELDS
#undef LC_GCODE_M_COMMAND_FIELD

bool lc_gcode_m_command_handle_attributes(lc_gcode_m_command_t *m_command, const char *line);

#endif