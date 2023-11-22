#include <string.h>

#include "map.h"
#include "data_structures/list/list.h"

// Macros for endianness handling
#define IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

#define INITIAL_CAPACITY 32
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct
{
    void *key_data;
    size_t key_size;
} lc_map_key_t;

typedef struct
{
    void *value_data;
    size_t value_size;
} lc_map_value_t;

typedef struct
{
    lc_map_key_t *key;
    lc_map_value_t *value;
} lc_map_key_value_pair_t;

struct _lc_map_t
{
    lc_list_t **buckets_list;
    size_t capacity;
    size_t size;
};

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static uint32_t lc_map_murmurhash3(const void *key, int len, uint32_t seed);
static inline void lc_map_resize_capacity(lc_map_t *map);
static inline lc_map_key_value_pair_t *lc_map_create_pair(void *key_data, size_t key_size, void *value_data, size_t value_size);
static lc_map_key_value_pair_t *lc_map_get_pair(lc_map_t *map, void *key_data, size_t key_size);
static size_t lc_map_get_index(lc_map_t *map, void *key_data, size_t key_size);
/******************************************************/

lc_map_t *lc_map_create()
{
    lc_map_t *map = (lc_map_t *)_malloc(sizeof(lc_map_t));

    LC_ASSERT(map, "Map memory allocation failed!");

    map->buckets_list = (lc_list_t **)calloc(INITIAL_CAPACITY, sizeof(lc_list_t *));
    map->capacity = INITIAL_CAPACITY;
    map->size = 0;

    LC_ASSERT(map->buckets_list, "map buckets memory allocation failed!");

    for (size_t i = 0; i < map->capacity; i++)
        map->buckets_list[i] = lc_list_create();

    return map;
}

void lc_map_destroy(lc_map_t *map)
{
    lc_map_clear(map);

    for (size_t i = 0; i < map->capacity; i++)
        lc_list_destroy(map->buckets_list[i]);

    _free(map->buckets_list);
    _free(map);
}

void lc_map_insert(lc_map_t *map, void *key, size_t key_size, void *value, size_t value_size)
{
    lc_map_key_value_pair_t *pair = lc_map_get_pair(map, key, key_size);
    if (pair)
    {
        _free(pair->value->value_data);

        pair->value->value_data = _malloc(value_size);

        LC_ASSERT(pair->value, "map value type memory allocation failed!");

        pair->value->value_size = value_size;

        memcpy(pair->value->value_data, value, value_size);

        return;
    }

    // Check load factor and resize if necessary
    if ((double)map->size / map->capacity > LOAD_FACTOR_THRESHOLD)
        lc_map_resize_capacity(map);

    uint32_t index = lc_map_get_index(map, key, key_size);

    pair = lc_map_create_pair(key, key_size, value, value_size);

    lc_list_insert_back(map->buckets_list[index], pair);

    map->size++;
}

void lc_map_erase(lc_map_t *map, void *key, size_t key_size)
{
    lc_map_key_value_pair_t *pair = lc_map_get_pair(map, key, key_size);

    if (!pair)
        return;

    size_t list_index = lc_map_get_index(map, key, key_size);

    (void)lc_list_pop_at(map->buckets_list[list_index], lc_list_get_index(map->buckets_list[list_index], pair));

    _free(pair->key->key_data);
    _free(pair->key);
    _free(pair->value->value_data);
    _free(pair->value);
    _free(pair);

    map->size--;
}

bool lc_map_find(lc_map_t *map, void *key, size_t key_size, void **value, size_t *value_size)
{
    lc_map_key_value_pair_t *pair = lc_map_get_pair(map, key, key_size);

    if (pair)
    {
        *value = pair->value->value_data;
        *value_size = pair->value->value_size;

        return true;
    }

    // Key not found
    return false;
}

void lc_map_foreach(lc_map_t *map, lc_map_foreach_cb_t cb, void *user_data)
{
    for (size_t i = 0; i < map->capacity; i++)
    {
        lc_map_key_value_pair_t *pair = NULL;

        LIST_FOREACH(map->buckets_list[i], pair)
        {
            if (cb)
                cb(pair->key->key_data, pair->key->key_size, pair->value->value_data, pair->value->value_size, user_data);
        }
    }
}

size_t lc_map_get_size(lc_map_t *map)
{
    return map->size;
}

void lc_map_clear(lc_map_t *map)
{
    for (size_t i = 0; i < map->capacity; i++)
    {
        lc_map_key_value_pair_t *pair = NULL;

        LIST_FOREACH(map->buckets_list[i], pair)
        {
            _free(pair->key->key_data);
            _free(pair->key);
            _free(pair->value->value_data);
            _free(pair->value);
            _free(pair);
        }

        lc_list_clear(map->buckets_list[i]);
    }

    map->size = 0;
}

/******************************************************/
/***********static functions implementations***********/
/******************************************************/
static uint32_t lc_map_murmurhash3(const void *key, int len, uint32_t seed)
{
    const uint8_t *data = (const uint8_t *)key;
    const int nblocks = len / 4;

    uint32_t h = seed;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    // Body
    const uint32_t *blocks = (const uint32_t *)(data + nblocks * 4);
    for (int i = -nblocks; i; i++)
    {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> 17);
        k1 *= c2;

        h ^= k1;
        h = (h << 13) | (h >> 19);
        h = h * 5 + 0xe6546b64;
    }

    // Tail
    const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);
    uint32_t k1 = 0;
    switch (len & 3)
    {
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0];
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> 17);
        k1 *= c2;
        h ^= k1;
    };

    // Finalization
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

// Output adjustment for endianness
#if IS_BIG_ENDIAN
    // Adjust byte order for big-endian architectures
    h = ((h & 0xFF000000) >> 24) | ((h & 0x00FF0000) >> 8) | ((h & 0x0000FF00) << 8) | ((h & 0x000000FF) << 24);
#endif

    return h;
}

static inline void lc_map_resize_capacity(lc_map_t *map)
{
    size_t new_capacity = map->capacity * 2;

    lc_list_t **new_bucket_list = (lc_list_t **)calloc(new_capacity, sizeof(lc_list_t *));

    for (size_t i = 0; i < new_capacity; i++)
        new_bucket_list[i] = lc_list_create();

    for (size_t i = 0; i < map->capacity; i++)
    {
        lc_map_key_value_pair_t *pair = NULL;

        LIST_FOREACH(map->buckets_list[i], pair)
        {
            size_t new_index = lc_map_murmurhash3(pair->key->key_data, pair->key->key_size, 0) % new_capacity;
            lc_list_insert_back(new_bucket_list[new_index], pair);
        }

        lc_list_destroy(map->buckets_list[i]);
    }

    _free(map->buckets_list);

    map->buckets_list = new_bucket_list;
    map->capacity = new_capacity;
}

static inline lc_map_key_value_pair_t *lc_map_create_pair(void *key_data, size_t key_size, void *value_data, size_t value_size)
{
    lc_map_key_value_pair_t *pair = (lc_map_key_value_pair_t *)_malloc(sizeof(lc_map_key_value_pair_t));

    LC_ASSERT(pair, "map key value pair memory allocation failed!");

    pair->key = (lc_map_key_t *)_malloc(sizeof(lc_map_key_t));
    LC_ASSERT(pair->key, "map key type memory allocation failed!");
    pair->key->key_size = key_size;
    pair->key->key_data = _malloc(key_size);
    LC_ASSERT(pair->key->key_data, "map key data memory allocation failed!");
    memcpy(pair->key->key_data, key_data, key_size);

    pair->value = (lc_map_value_t *)_malloc(sizeof(lc_map_value_t));
    LC_ASSERT(pair->value, "map value type memory allocation failed!");
    pair->value->value_size = value_size;
    pair->value->value_data = _malloc(value_size);
    LC_ASSERT(pair->value->value_data, "map value data memory allocation failed!");
    memcpy(pair->value->value_data, value_data, value_size);

    return pair;
}

static lc_map_key_value_pair_t *lc_map_get_pair(lc_map_t *map, void *key_data, size_t key_size)
{
    uint32_t index = lc_map_murmurhash3(key_data, key_size, 0) % map->capacity;

    lc_map_key_value_pair_t *pair = NULL;

    LIST_FOREACH(map->buckets_list[index], pair)
    if (!memcmp(key_data, pair->key->key_data, key_size))
        return pair;

    return NULL;
}

static size_t lc_map_get_index(lc_map_t *map, void *key_data, size_t key_size)
{
    return lc_map_murmurhash3(key_data, key_size, 0) % map->capacity;
}
/******************************************************/