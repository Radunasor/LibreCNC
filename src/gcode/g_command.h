#ifndef G_COMMAND_H
#define G_COMMAND_H

#include "common_defs.h"
#include "gcode_base_obj.h"

#define LC_GCODE_G_COMMAND_ATTR_GETTER(ATTR) \
            bool inline lc_gcode_g_command_get_attr_##ATTR(lc_gcode_obj_t *command, float *value) \
            {                                                                                     \
                lc_gcode_g_command_t *g_command = (lc_gcode_g_command_t *) command;               \
                LC_ASSERT(command, "gcode obj can't be a NULL pointer!");                         \
                *value = g_command->ATTR.value;                                                   \
                return g_command->ATTR.existed;                                                   \
            };

typedef struct lc_gcode_g_command_st lc_gcode_g_command_t;
typedef void (*lc_gcode_g_command_hanler_cb_t)(const lc_gcode_obj_t *);

typedef struct lc_gcode_g_command_attr_st
{
    bool existed;
    float value;
} lc_gcode_g_command_attr_t;

struct lc_gcode_g_command_st
{
    lc_gcode_obj_t command;
    lc_gcode_g_command_attr_t X;
    lc_gcode_g_command_attr_t Y;
    lc_gcode_g_command_attr_t Z;
    lc_gcode_g_command_attr_t I;
    lc_gcode_g_command_attr_t J;
    lc_gcode_g_command_attr_t K;
    lc_gcode_g_command_attr_t L;
    lc_gcode_g_command_attr_t N;
    lc_gcode_g_command_attr_t P;
    lc_gcode_g_command_attr_t R;
    lc_gcode_g_command_attr_t S;
    lc_gcode_g_command_attr_t T;
};

// will add accessor func named lc_gcode_g_command_get_attr_X/Y/Z...()
LC_GCODE_G_COMMAND_ATTR_GETTER(X);
LC_GCODE_G_COMMAND_ATTR_GETTER(Y);
LC_GCODE_G_COMMAND_ATTR_GETTER(Z);
LC_GCODE_G_COMMAND_ATTR_GETTER(I);
LC_GCODE_G_COMMAND_ATTR_GETTER(J);
LC_GCODE_G_COMMAND_ATTR_GETTER(K);
LC_GCODE_G_COMMAND_ATTR_GETTER(L);
LC_GCODE_G_COMMAND_ATTR_GETTER(N);
LC_GCODE_G_COMMAND_ATTR_GETTER(P);
LC_GCODE_G_COMMAND_ATTR_GETTER(R);
LC_GCODE_G_COMMAND_ATTR_GETTER(S);
LC_GCODE_G_COMMAND_ATTR_GETTER(T);

bool lc_gcode_g_command_extract_values(lc_gcode_obj_t *command, const char *line);
void lc_gcode_g_command_set_handler_callback(lc_gcode_g_command_hanler_cb_t callback);

#endif