#include "librecnc.h"

#include "config/config.h"
#include "planner/planner.h"

static bool initialized = false;

void lc_init()
{
    if (initialized)
        return;

    lc_config_init();
    lc_config_load_default_configs();
    lc_planner_init();

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

    lc_planner_deinit();
    lc_config_deinit();

    initialized = false;
}

void lc_handler()
{
    lc_planner_plan();
}