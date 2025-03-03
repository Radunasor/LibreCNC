#include "config/config.h"
#include "data_structures/map/map.h"

#include "config/default_configs.h"

static bool initialized = false;
static lc_map_t *config_map = NULL;

/******************************************************/
/***********static functions declarations**************/
/******************************************************/

/******************************************************/

void lc_config_init()
{
    if (initialized)
        return;

    config_map = lc_map_create();

    if (config_map)
        initialized = true;
}

void lc_config_deinit()
{
    if (!initialized)
        return;

    lc_map_destroy(config_map);
    config_map = NULL;
    initialized = false;
}

bool lc_config_get_initialized()
{
    return initialized;
}

void lc_config_load_default_configs()
{
    CHECK_INITIALIIZED

    uint16_t conf_idx = 0;
    while (&(default_config_table[conf_idx].key) != NULL)
    {
        lc_config_set_float(default_config_table[conf_idx].key, default_config_table[conf_idx].value);
        conf_idx++;
    }
}

void lc_config_set_bool(lc_config_key_t key, const bool value)
{
    CHECK_INITIALIIZED

    lc_map_insert(config_map, &key.key, key.key_size, (void *)&value, sizeof(bool));
}

void lc_config_set_int(lc_config_key_t key, const int value)
{
    CHECK_INITIALIIZED

    lc_map_insert(config_map, &key.key, key.key_size, (void *)&value, sizeof(int));
}

void lc_config_set_float(lc_config_key_t key, const float value)
{
    CHECK_INITIALIIZED

    lc_map_insert(config_map, &key.key, key.key_size, (void *)&value, sizeof(float));
}

void lc_config_set_data(lc_config_key_t key, const uint8_t *data, const size_t data_size)
{
    CHECK_INITIALIIZED

    lc_map_insert(config_map, &key.key, key.key_size, (void *)data, data_size);
}

bool lc_config_get_bool(lc_config_key_t key, bool *value)
{
    CHECK_INITIALIIZED

    size_t output_size = 0;

    bool *tmp_val = NULL;

    bool res = lc_map_find(config_map, &key.key, key.key_size, (void **)&tmp_val, &output_size);

    if (res)
        *value = *tmp_val;

    return res;
}

bool lc_config_get_int(lc_config_key_t key, int *value)
{
    CHECK_INITIALIIZED

    size_t output_size = 0;
    int *tmp_val = NULL;

    bool res = lc_map_find(config_map, &key.key, key.key_size, (void **)&tmp_val, &output_size);
    if (res)
        *value = *tmp_val;

    return res;
}

bool lc_config_get_float(lc_config_key_t key, float *value)
{
    CHECK_INITIALIIZED

    size_t output_size = 0;

    float *tmp_val = NULL;

    bool res = lc_map_find(config_map, &key.key, key.key_size, (void **)&tmp_val, &output_size);
    if (res)
        *value = *tmp_val;

    return res;
}

bool lc_config_get_data(lc_config_key_t key, uint8_t **value, size_t *data_size)
{
    CHECK_INITIALIIZED

    return lc_map_find(config_map, &key.key, key.key_size, (void **)value, data_size);
}

/******************************************************/
/***********static functions implementations***********/
/******************************************************/

/******************************************************/