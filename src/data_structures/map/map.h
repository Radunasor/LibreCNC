/**
 * @file map.h
 * @brief Header file for a generic hashmap (key-value pair) implementation.
 *
 * This file defines the interface for a generic hashmap data structure.
 */

#ifndef MAP_H
#define MAP_H

#include "platform_defs.h"

/**
 * @struct lc_map_t
 * @brief Structure representing a hashmap (key-value pair).
 *
 * An instance of this structure is used to represent a hashmap.
 * The details of the implementation are hidden from the users.
 */
typedef struct _lc_map_t lc_map_t;

/**
 * @typedef lc_map_foreach_cb_t
 * @brief Function pointer type for the callback function used in foreach operations.
 *
 * This function type is used as a callback for iterating over key-value pairs in the hashmap.
 */
typedef void (*lc_map_foreach_cb_t)(void *key_data, size_t key_size, void *value_data, size_t value_size, void *user_data);

/**
 * @brief Creates a new hashmap.
 *
 * @return A pointer to the newly created hashmap.
 */
lc_map_t *lc_map_create();

/**
 * @brief Destroys a hashmap and frees associated memory.
 *
 * @param map The hashmap to be destroyed.
 */
void lc_map_destroy(lc_map_t *map);

/**
 * @brief Inserts a key-value pair into the hashmap.
 *
 * @param map The hashmap to which the key-value pair is to be added.
 * @param key The key to be inserted.
 * @param key_size The size of the key.
 * @param data The value associated with the key.
 * @param data_size The size of the value data.
 */
void lc_map_insert(lc_map_t *map, void *key, size_t key_size, void *data, size_t data_size);

/**
 * @brief Removes a key-value pair from the hashmap.
 *
 * @param map The hashmap from which the key-value pair is to be removed.
 * @param key The key to be erased.
 * @param key_size The size of the key.
 * @return A pointer to the data associated with the erased key.
 */
void *lc_map_erase(lc_map_t *map, void *key, size_t key_size);

/**
 * @brief Finds a key-value pair in the hashmap.
 *
 * @param map The hashmap in which the key-value pair is to be found.
 * @param key The key to be found.
 * @param key_size The size of the key.
 * @param value A pointer to store the found value.
 * @param value_size A pointer to store the size of the found value.
 * @return A boolean indicating whether the key was found in the hashmap.
 */
bool lc_map_find(lc_map_t *map, void *key, size_t key_size, void **value, size_t *value_size);

/**
 * @brief Applies a callback function to each key-value pair in the hashmap.
 *
 * @param map The hashmap to be traversed.
 * @param cb The callback function to be applied to each key-value pair.
 * @param user_data User-defined data to be passed to the callback function.
 */
void lc_map_foreach(lc_map_t *map, lc_map_foreach_cb_t cb, void *user_data);

/**
 * @brief Gets the current size of the hashmap.
 *
 * @param map The hashmap for which the size is to be determined.
 * @return The current size of the hashmap.
 */
size_t lc_map_get_size(lc_map_t *map);

/**
 * @brief Clears all key-value pairs from the hashmap.
 *
 * @param map The hashmap to be cleared.
 */
void lc_map_clear(lc_map_t *map);
#endif