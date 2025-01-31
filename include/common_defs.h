#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "librecnc_config.h"
#include "logger/logger.h"

#if defined(__STDC__) && __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
typedef enum
{
    false,
    true
} bool;
#endif

#define lc_malloc malloc
#define lc_free free

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) < (y) ? (y) : (x))

#ifdef NDEBUG

#define LC_ASSERT(expr, msg)
#define LC_RELEASE_BUILD

#else

#define LC_ASSERT_HANDLER \
    while (1)             \
        ;

#define LC_ASSERT(expr, msg)                                                                                                  \
    do                                                                                                                        \
    {                                                                                                                         \
        if (!(expr))                                                                                                          \
        {                                                                                                                     \
            LC_LOG_ERROR("[Asserted]: %s (expr: %s | file: %s:%d | func: %s)", msg, #expr, __FILE__, __LINE__, __FUNCTION__); \
            LC_ASSERT_HANDLER                                                                                                 \
        }                                                                                                                     \
    } while (0)

#define CHECK_INITIALIIZED LC_ASSERT(initialized, "GCODE module not initialized!");

#define LC_DEBUG_BUILD

#endif

#endif