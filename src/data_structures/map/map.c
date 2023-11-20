#include <string.h>

#include "map.h"
#include "data_structures/list/list.h"

// Macros for endianness handling
#define IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

#define INITIAL_CAPACITY 4
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

// MurmurHash3 implementation
static uint32_t murmurhash3(const void *key, int len, uint32_t seed)
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

    _free(map);
}

static inline void resize_capacity(lc_map_t *map)
{
    size_t new_capacity = map->capacity * 2;
    map->buckets_list = (lc_list_t **)realloc(map->buckets_list, new_capacity * sizeof(lc_list_t *));
    memset(map->buckets_list + map->capacity, 0, (new_capacity - map->capacity) * sizeof(lc_list_t *));
    map->capacity = new_capacity;
}

void lc_map_insert(lc_map_t *map, void *key, size_t key_size, void *value, size_t value_size)
{
    // Check load factor and resize if necessary
    if ((double)map->size / map->capacity > LOAD_FACTOR_THRESHOLD)
        resize_capacity(map);

    uint32_t index = murmurhash3(key, key_size, 0) % map->capacity;

    lc_map_key_value_pair_t *pair = (lc_map_key_value_pair_t *)_malloc(sizeof(lc_map_key_value_pair_t));

    LC_ASSERT(pair, "map key value pair memory allocation failed!");

    pair->key = (lc_map_key_t *)_malloc(sizeof(lc_map_key_t));
    LC_ASSERT(pair->key, "map key type memory allocation failed!");
    pair->key->key_size = key_size;
    pair->key->key_data = _malloc(key_size);
    LC_ASSERT(pair->key->key_data, "map key data memory allocation failed!");
    memcpy(pair->key->key_data, key, key_size);

    pair->value = (lc_map_value_t *)_malloc(sizeof(lc_map_value_t));
    LC_ASSERT(pair->value, "map value type memory allocation failed!");
    pair->value->value_size = value_size;
    pair->value->value_data = _malloc(value_size);
    LC_ASSERT(pair->value->value_data, "map value data memory allocation failed!");
    memcpy(pair->value->value_data, value, value_size);

    lc_list_insert_back(map->buckets_list[index], pair);

    map->size++;
}

void *lc_map_remove(lc_map_t *map, void *key)
{
}

void *lc_map_find(lc_map_t *map, void *key, size_t key_size)
{
    uint32_t index = murmurhash3(key, key_size, 0) % map->capacity;

    lc_map_key_value_pair_t *pair = NULL;

    LIST_FOREACH(map->buckets_list[index], pair)
    if (!memcmp(key, pair->key->key_data, key_size))
        return pair->value->value_data;

    // Key not found
    return NULL;
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
