#ifndef PLATFORM_DEFS_H
#define PLATFORM_DEFS_H

#include "librecnc_config.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__STDC__) && __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
typedef enum
{
    false,
    true
} bool;
#endif

#endif