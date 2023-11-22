#ifndef CONFIG_H
#define CONFIG_H

#include "config_keys.h"
#include "platform_defs.h"

void lc_config_init();
void lc_config_deinit();

void lc_config_set_bool(lc_config_key_t key, const bool value);
void lc_config_set_int(lc_config_key_t key, const int value);
void lc_config_set_float(lc_config_key_t key, const float value);
void lc_config_set_data(lc_config_key_t key, const uint8_t *data, const size_t data_size);

bool lc_config_get_bool(lc_config_key_t key, bool *value);
bool lc_config_get_int(lc_config_key_t key, int *value);
bool lc_config_get_float(lc_config_key_t key, float *value);
bool lc_config_get_data(lc_config_key_t key, uint8_t **value, size_t *data_size);

#endif