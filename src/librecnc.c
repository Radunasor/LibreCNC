#include "librecnc.h"

#include "config/config.h"

static bool initialized = false;

void lc_init()
{
    if (initialized)
        return;

    lc_config_init();

    initialized = true;
}

bool lc_get_initialized()
{
    return initialized;
}

void lc_deinit()
{
    if (!initialized)
        return;

    lc_config_deinit();

    initialized = false;
}