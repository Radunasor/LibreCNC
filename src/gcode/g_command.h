#ifndef G_COMMAND_H
#define G_COMMAND_H

#include "common_defs.h"
#include "gcode_base_obj.h"
#include "utils.h"

typedef struct lc_gcode_g_command_st lc_gcode_g_command_t;
typedef void (*lc_gcode_g_command_hanler_cb_t)(const lc_gcode_obj_t *);

typedef struct lc_gcode_g_command_attr_st
{
    bool existed;
    float value;
} lc_gcode_g_command_attr_t;

#define LC_GCODE_G_COMMAND_SUPPORTED_FIELDS \
    LC_GCODE_G_COMMAND_FIELD(X) \
    LC_GCODE_G_COMMAND_FIELD(Y) \
    LC_GCODE_G_COMMAND_FIELD(Z) \
    LC_GCODE_G_COMMAND_FIELD(I) \
    LC_GCODE_G_COMMAND_FIELD(J) \
    LC_GCODE_G_COMMAND_FIELD(K) \
    LC_GCODE_G_COMMAND_FIELD(L) \
    LC_GCODE_G_COMMAND_FIELD(N) \
    LC_GCODE_G_COMMAND_FIELD(P) \
    LC_GCODE_G_COMMAND_FIELD(R) \
    LC_GCODE_G_COMMAND_FIELD(S) \
    LC_GCODE_G_COMMAND_FIELD(T)

struct lc_gcode_g_command_st
{
    lc_gcode_obj_t command;
    #define LC_GCODE_G_COMMAND_FIELD(attr) lc_gcode_g_command_attr_t attr;
    LC_GCODE_G_COMMAND_SUPPORTED_FIELDS
    #undef LC_GCODE_G_COMMAND_FIELD
};

// will add accessor func named lc_gcode_g_command_get_attr_X/Y/Z...()
#define LC_GCODE_G_COMMAND_FIELD(attr) LC_GCODE_COMMAND_ATTR_ACCESSOR_GENERATOR(g, lc_gcode_g_command_t, attr)
LC_GCODE_G_COMMAND_SUPPORTED_FIELDS
#undef LC_GCODE_G_COMMAND_FIELD

bool lc_gcode_g_command_extract_values(lc_gcode_obj_t *command, const char *line);
void lc_gcode_g_command_set_handler_callback(lc_gcode_g_command_hanler_cb_t callback);

#endif