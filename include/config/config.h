/**
 * @file config.h
 * @brief Header file for a configuration management module.
 *
 * This file defines the interface for managing configuration settings.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>

#include "config_keys.h"
#include "common_defs.h"

#define LC_CONFIG_STRING_KEY_MAX_LENTGH 128

typedef struct
{
  void *key;
  size_t key_size;
} lc_config_key_t;

#define LC_CONFIG_KEY_BIN(conf_key, conf_key_size)                   \
  (lc_config_key_t)                                                  \
  {                                                                  \
    .key = (void *)(uintptr_t)conf_key,                                         \
    .key_size = MIN(conf_key_size, LC_CONFIG_STRING_KEY_MAX_LENTGH)  \
  }

#define LC_CONFIG_KEY_INT(conf_key) LC_CONFIG_KEY_BIN(conf_key, sizeof(conf_key))

#define LC_CONFIG_KEY_STRING(conf_key) LC_CONFIG_KEY_BIN(conf_key, strlen(conf_key) + 1)

/**
 * @brief Initializes the configuration module.
 */
void lc_config_init();

/**
 * @brief Deinitializes the configuration module.
 */
void lc_config_deinit();

/**
 * @brief check for the initialization status.
 */
bool lc_config_get_initialized();

/**
 * @brief Loads default configurations into the configuration module.
 */
void lc_config_load_default_configs();

/**
 * @brief Sets a boolean configuration value.
 *
 * @param key The configuration key.
 * @param value The boolean value to be set.
 */
void lc_config_set_bool(lc_config_key_t key, const bool value);

/**
 * @brief Sets an integer configuration value.
 *
 * @param key The configuration key.
 * @param value The integer value to be set.
 */
void lc_config_set_int(lc_config_key_t key, const int value);

/**
 * @brief Sets a float configuration value.
 *
 * @param key The configuration key.
 * @param value The float value to be set.
 */
void lc_config_set_float(lc_config_key_t key, const float value);

/**
 * @brief Sets a data configuration value.
 *
 * @param key The configuration key.
 * @param data A pointer to the data to be set.
 * @param data_size The size of the data.
 */
void lc_config_set_data(lc_config_key_t key, const uint8_t *data, const size_t data_size);

/**
 * @brief Gets a boolean configuration value.
 *
 * @param key The configuration key.
 * @param value A pointer to store the retrieved boolean value.
 * @return A boolean indicating whether the retrieval was successful.
 */
bool lc_config_get_bool(lc_config_key_t key, bool *value);

/**
 * @brief Gets an integer configuration value.
 *
 * @param key The configuration key.
 * @param value A pointer to store the retrieved integer value.
 * @return A boolean indicating whether the retrieval was successful.
 */
bool lc_config_get_int(lc_config_key_t key, int *value);

/**
 * @brief Gets a float configuration value.
 *
 * @param key The configuration key.
 * @param value A pointer to store the retrieved float value.
 * @return A boolean indicating whether the retrieval was successful.
 */
bool lc_config_get_float(lc_config_key_t key, float *value);

/**
 * @brief Gets a bytearray configuration value.
 *
 * @param key The configuration key.
 * @param value A pointer to store the retrieved data.
 * @param data_size A pointer to store the size of the retrieved data.
 * @return A boolean indicating whether the retrieval was successful.
 */
bool lc_config_get_data(lc_config_key_t key, uint8_t **value, size_t *data_size);

#endif // CONFIG_H