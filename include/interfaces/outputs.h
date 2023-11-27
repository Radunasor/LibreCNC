#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "common_defs.h"

typedef struct
{
    void (*lc_interface_output_x_axis_pulse)(bool state, bool dir);
    void (*lc_interface_output_y_axis_pulse)(bool state, bool dir);
    void (*lc_interface_output_z_axis_pulse)(bool state, bool dir);

    void (*lc_interface_output_spindle_control)(bool state);
    void (*lc_interface_output_coolant_control)(bool state);
} lc_interface_output_t;

#endif