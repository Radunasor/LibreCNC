#ifndef MOTORS_H
#define MOTORS_H

#include "platform_defs.h"

typedef struct
{
    void (*lc_interface_motor_x_axis_pulse)(bool state, bool dir);
    void (*lc_interface_motor_y_axis_pulse)(bool state, bool dir);
    void (*lc_interface_motor_z_axis_pulse)(bool state, bool dir);
} lc_interfac_motors_t;

#endif