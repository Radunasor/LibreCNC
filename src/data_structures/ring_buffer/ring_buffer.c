#include "ring_buffer.h"

struct _lc_ring_buffer_t
{
    void **buffer;
    int head;
    int tail;
    int size;
    int count; // Add a count variable to keep track of the number of elements
};

lc_ring_buffer_t *lc_ring_buffer_create(size_t size)
{
    lc_ring_buffer_t *rb = _malloc(sizeof(lc_ring_buffer_t));

    LC_ASSERT(rb, "ring buffer memory allocation failed!");

    rb->buffer = _malloc(size * sizeof(void *));

    LC_ASSERT(rb->buffer, "ring buffer data memory allocation failed!");

    rb->head = 0;
    rb->tail = 0;
    rb->size = size;
    rb->count = 0; // Initialize count to 0

    return rb;
}

void lc_ring_buffer_destroy(lc_ring_buffer_t *rb)
{
    LC_ASSERT(rb, "ring buffer pointer is NULL");

    if (rb->buffer != NULL)
    {
        _free(rb->buffer);
        rb->buffer = NULL;
    }

    _free(rb);
}

void lc_ring_buffer_insert(lc_ring_buffer_t *rb, void *data)
{
    LC_ASSERT(data, "data pointer is NULL"); // Check if data is NULL

    if (rb->count == rb->size) // Check if the buffer is full
    {
        LC_LOG_WARN("Buffer is full");
        return; // Return an error value
    }

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->size;
    rb->count++; // Increment count
}

void *lc_ring_buffer_remove(lc_ring_buffer_t *rb)
{
    if (rb->head == rb->tail)
    {
        LC_LOG_WARN("Buffer is empty");
        return NULL; // Return an error value
    }

    void *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    rb->count--; // Decrement count
    return data;
}

size_t lc_ring_buffer_get_elemets_count(lc_ring_buffer_t *rb)
{
    return rb->count;
}

size_t lc_ring_buffer_get_size(lc_ring_buffer_t *rb)
{
    return rb->size;
}