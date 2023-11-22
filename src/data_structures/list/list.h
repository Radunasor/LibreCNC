/**
 * @file list.h
 * @brief Header file for a generic linked list implementation.
 *
 * This file defines the interface for a generic linked list.
 */

#ifndef LIST_H
#define LIST_H

#include "platform_defs.h"

#define LIST_FOREACH(list, node_data) for (size_t fei = 0; fei < lc_list_get_size(list) && (node_data = lc_list_find_at(list, fei), 1); ++fei)

/**
 * @struct lc_list_t
 * @brief Structure representing a linked list.
 *
 * An instance of this structure is used to represent a linked list.
 * The details of the implementation are hidden from the users.
 */
typedef struct _lc_list_t lc_list_t;

/**
 * @brief Creates a new linked list.
 *
 * @return A pointer to the newly created linked list.
 */
lc_list_t *lc_list_create();

/**
 * @brief Destroys a linked list and frees associated memory.
 *
 * @param list The linked list to be destroyed.
 */
void lc_list_destroy(lc_list_t *list);

/**
 * @brief Inserts data at the front of the linked list.
 *
 * @param list The linked list to which data is to be added.
 * @param data The data to be inserted.
 */
void lc_list_insert_front(lc_list_t *list, void *data);

/**
 * @brief Inserts data at the back of the linked list.
 *
 * @param list The linked list to which data is to be added.
 * @param data The data to be inserted.
 */
void lc_list_insert_back(lc_list_t *list, void *data);

/**
 * @brief Inserts data at a specified index in the linked list.
 *
 * @param list The linked list to which data is to be added.
 * @param index The index at which the data should be inserted. Index must be within the Linkedlist range.
 * @param data The data to be inserted.
 */
void lc_list_insert_at(lc_list_t *list, size_t index, void *data);

/**
 * @brief Removes and returns the data from the front of the linked list.
 *
 * @param list The linked list from which data is to be removed.
 * @return The data removed from the front of the linked list.
 */
void *lc_list_pop_front(lc_list_t *list);

/**
 * @brief Removes and returns the data from the back of the linked list.
 *
 * @param list The linked list from which data is to be removed.
 * @return The data removed from the back of the linked list.
 */
void *lc_list_pop_back(lc_list_t *list);

/**
 * @brief Removes and returns the data at a specified index in the linked list.
 *
 * @param list The linked list from which data is to be removed.
 * @param index The index at which the data should be removed. Index must be within the Linkedlist range.
 * @return The data removed from the specified index in the linked list.
 */
void *lc_list_pop_at(lc_list_t *list, size_t index);

/**
 * @brief Clears all elements from the linked list.
 *
 * @param list The linked list to be cleared.
 */
void lc_list_clear(lc_list_t *list);

/**
 * @brief Finds and returns the data at a specified index in the linked list.
 *
 * @param list The linked list in which data is to be found.
 * @param index The index at which the data should be found. Index must be within the Linkedlist range.
 * @return The data found at the specified index in the linked list.
 */
void *lc_list_find_at(lc_list_t *list, size_t index);

/**
 * @brief Finds and returns the index of the specified data in the linked list.
 *
 * @param list The linked list in which data is to be found.
 * @param data The data for which the index is to be found.
 * @return The index of the specified data in the linked list.
 */
size_t lc_list_get_index(lc_list_t *list, void *data);

/**
 * @brief Gets the current size of the linked list.
 *
 * @param list The linked list for which the size is to be determined.
 * @return The current size of the linked list.
 */
size_t lc_list_get_size(lc_list_t *list);
#endif // LIST_H