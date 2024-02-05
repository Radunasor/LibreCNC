#ifndef STEPPER_H
#define STEPPER_H

#include "common_defs.h"

typedef struct lc_stepper_st
{
    uint32_t steps;
    bool direction;
    float speed;        // Axis-limit adjusted nominal speed for this block in (mm/min)^2
    float acceleration; // Axis-limit adjusted line acceleration in (mm/min^2)
} lc_stepper_t;

#endif