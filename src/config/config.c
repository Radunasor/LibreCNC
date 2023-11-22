#include "config/config.h"
#include "data_structures/map/map.h"

static lc_map_t *config_map = NULL;

void lc_config_init()
{
    if (config_map)
        return;

    config_map = lc_map_create();
}

void lc_config_deinit()
{
    if (!config_map)
        return;

    lc_map_destroy(config_map);

    config_map = NULL;
}

void lc_config_set_bool(lc_config_key_t key, const bool value)
{
    lc_map_insert(config_map, &key, sizeof(lc_config_key_t), (void *)&value, sizeof(bool));
}

void lc_config_set_int(lc_config_key_t key, const int value)
{
    lc_map_insert(config_map, &key, sizeof(lc_config_key_t), (void *)&value, sizeof(int));
}

void lc_config_set_float(lc_config_key_t key, const float value)
{
    lc_map_insert(config_map, &key, sizeof(lc_config_key_t), (void *)&value, sizeof(float));
}

void lc_config_set_data(lc_config_key_t key, const uint8_t *data, const size_t data_size)
{
    lc_map_insert(config_map, &key, sizeof(lc_config_key_t), (void *)data, data_size);
}

bool lc_config_get_bool(lc_config_key_t key, bool *value)
{
    size_t output_size = 0;

    bool *tmp_val = NULL;

    bool res = lc_map_find(config_map, &key, sizeof(lc_config_key_t), (void **)&tmp_val, &output_size);

    if (res)
        *value = *tmp_val;

    return res;
}

bool lc_config_get_int(lc_config_key_t key, int *value)
{
    size_t output_size = 0;
    int *tmp_val = NULL;

    bool res = lc_map_find(config_map, &key, sizeof(lc_config_key_t), (void **)&tmp_val, &output_size);
    if (res)
        *value = *tmp_val;

    return res;
}

bool lc_config_get_float(lc_config_key_t key, float *value)
{
    size_t output_size = 0;

    float *tmp_val = NULL;

    bool res = lc_map_find(config_map, &key, sizeof(lc_config_key_t), (void **)&tmp_val, &output_size);
    if (res)
        *value = *tmp_val;

    return res;
}

bool lc_config_get_data(lc_config_key_t key, uint8_t **value, size_t *data_size)
{
    return lc_map_find(config_map, &key, sizeof(lc_config_key_t), (void **)value, data_size);
}
