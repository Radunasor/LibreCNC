#ifndef LIST_H
#define LIST_H

#include "platform_defs.h"

#define LIST_LOOP(list, node_data) for (size_t i = 0; i < lc_list_get_size(list); node_data = lc_list_find_at(list, i++))

typedef struct _lc_list_t lc_list_t;

typedef void (*lc_list_iterate_cb_t)(void *data);

lc_list_t *lc_list_create();
void lc_list_destroy(lc_list_t *list);

void lc_list_insert_front(lc_list_t *list, void *data);
void lc_list_insert_back(lc_list_t *list, void *data);
void lc_list_insert_at(lc_list_t *list, size_t index, void *data);

void *lc_list_pop_front(lc_list_t *list);
void *lc_list_pop_back(lc_list_t *list);
void *lc_list_pop_at(lc_list_t *list, size_t index);

void lc_list_clear(lc_list_t *list);

void *lc_list_find_at(lc_list_t *list, size_t index);
void lc_list_foreach(lc_list_t *list, lc_list_iterate_cb_t iter_cb);

bool lc_list_find(lc_list_t *list, void *data);

size_t lc_list_get_size(lc_list_t *list);
#endif