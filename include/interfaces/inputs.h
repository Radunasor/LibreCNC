#ifndef INPUTS_H
#define INPUTS_H

#include "common_defs.h"

typedef struct
{
    bool (*lc_interface_input_x_home_switch_trigged)();
    bool (*lc_interface_input_x_end_switch_trigged)();

    bool (*lc_interface_input_y_home_switch_trigged)();
    bool (*lc_interface_input_y_end_switch_trigged)();

    bool (*lc_interface_input_z_home_switch_trigged)();
    bool (*lc_interface_input_z_end_switch_trigged)();

    bool (*lc_interface_input_estop_switch_trigged)();
    bool (*lc_interface_input_probe_contact_trigged)();
} lc_interface_input_t;

#endif