#include "common_defs.h"

typedef struct _lc_ring_buffer_t lc_ring_buffer_t;

lc_ring_buffer_t *lc_ring_buffer_create(size_t size);
void lc_ring_buffer_destroy(lc_ring_buffer_t *rb);
void lc_ring_buffer_insert(lc_ring_buffer_t *rb, void *data);
void *lc_ring_buffer_remove(lc_ring_buffer_t *rb);
size_t lc_ring_buffer_get_elemets_count(lc_ring_buffer_t *rb);
size_t lc_ring_buffer_get_size(lc_ring_buffer_t *rb);
bool lc_ring_buffer_is_full(lc_ring_buffer_t *rb);