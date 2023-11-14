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

#define _malloc malloc
#define _free free

#ifdef NDEBUG

#define LC_ASSERT(expr, msg)

#else

#define LC_ASSERT_HANDLER \
    while (1)             \
        ;

// todo : need to change printf with LOG_CRITICAL
#define LC_ASSERT(expr, msg)                                                                         \
    do                                                                                               \
    {                                                                                                \
        if (!(expr))                                                                                 \
        {                                                                                            \
            printf("Asserted: %s (%s, %s, %s, %d)\n", msg, #expr, __FILE__, __FUNCTION__, __LINE__); \
            LC_ASSERT_HANDLER                                                                        \
        }                                                                                            \
    } while (0)

#endif

#endif