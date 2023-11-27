#ifndef LIMITS_H
#define LIMITS_H

#include "platform_defs.h"

typedef struct
{
    bool (*lc_interface_limits_x_axis_home)();
    bool (*lc_interface_limits_x_axis_end)();

    bool (*lc_interface_limits_y_axis_home)();
    bool (*lc_interface_limits_y_axis_end)();

    bool (*lc_interface_limits_z_axis_home)();
    bool (*lc_interface_limits_z_axis_end)();

    bool (*lc_interface_estop_switch_trigged)();
} lc_interfac_limits_t;

#endif