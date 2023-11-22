/**
 * @file config.h
 * @brief Header file for a configuration management module.
 *
 * This file defines the interface for managing configuration settings.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "config_keys.h"
#include "platform_defs.h"

/**
 * @struct lc_config_table_default_t
 * @brief Structure representing a default configuration entry.
 *
 * This structure associates a configuration key with its default float value.
 */
typedef struct
{
    lc_config_key_t key; ///< The configuration key.
    float value;         ///< The default float value associated with the key.
} lc_config_table_default_t;

/**
 * @brief Initializes the configuration module.
 */
void lc_config_init();

/**
 * @brief Deinitializes the configuration module.
 */
void lc_config_deinit();

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

#endif