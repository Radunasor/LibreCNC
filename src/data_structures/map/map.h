#ifndef MAP_H
#define MAP_H

#include "platform_defs.h"

typedef struct _lc_map_t lc_map_t;

lc_map_t *lc_map_create();
void lc_map_destroy(lc_map_t *map);

void lc_map_insert(lc_map_t *map, void *key, size_t key_size, void *data, size_t data_size);
void *lc_map_remove(lc_map_t *map, void *key);

void *lc_map_find(lc_map_t *map, void *key, size_t key_size);

void lc_map_clear(lc_map_t *map);
#endif