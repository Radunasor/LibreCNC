#include "ring_buffer.h"

#if 0

#include <string.h>

#define LC_PLANNER_GCODE_RB_BUFFER_SIZE 10

struct _lc_planner_rb_t
{
    lc_gcode_data_t buffer[LC_PLANNER_GCODE_RB_BUFFER_SIZE];
    int head;
    int tail;
    int size;
    int count; // Add a count variable to keep track of the number of elements
};

lc_planner_rb_t *lc_planner_rb_create(size_t size)
{
    lc_planner_rb_t *rb = lc_malloc(sizeof(lc_planner_rb_t));

    LC_ASSERT(rb, "ring buffer memory allocation failed!");

    memset(rb->buffer, 0, LC_PLANNER_GCODE_RB_BUFFER_SIZE * sizeof(lc_gcode_data_t));

    rb->head = 0;
    rb->tail = 0;
    rb->size = size;
    rb->count = 0; // Initialize count to 0

    return rb;
}

void lc_planner_rb_destroy(lc_planner_rb_t *rb)
{
    LC_ASSERT(rb, "ring buffer pointer is NULL");

    lc_free(rb);
}

bool lc_planner_rb_insert(lc_planner_rb_t *rb, lc_gcode_data_t data)
{
    LC_ASSERT(&data, "data pointer is NULL"); // Check if data is NULL

    if (rb->count == rb->size) // Check if the buffer is full
        return false;          // Return an error value

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->size;
    rb->count++; // Increment count
}

bool lc_planner_rb_remove(lc_planner_rb_t *rb, lc_gcode_data_t *data)
{
    if (rb->count == 0)
        return false; // Return an error value

    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    rb->count--; // Decrement count
    return data;

    return true;
}

size_t lc_planner_rb_get_elemets_count(lc_planner_rb_t *rb)
{
    return rb->count;
}

size_t lc_planner_rb_get_size(lc_planner_rb_t *rb)
{
    return rb->size;
}

bool lc_planner_rb_is_full(lc_planner_rb_t *rb)
{
    return rb->count == rb->size;
}

#endif