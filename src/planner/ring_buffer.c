#include <string.h>
#include "ring_buffer.h"

#define LC_PLANNER_GCODE_RB_BUFFER_SIZE 20

struct lc_planner_rb_st
{
    lc_gcode_obj_t buffer[LC_PLANNER_GCODE_RB_BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t size;
    size_t count; // Add a count variable to keep track of the number of elements
};

lc_planner_rb_t *lc_planner_rb_create(size_t size)
{
    lc_planner_rb_t *rb = lc_malloc(sizeof(lc_planner_rb_t));

    LC_ASSERT(rb, "ring buffer memory allocation failed!");

    memset(rb->buffer, 0, LC_PLANNER_GCODE_RB_BUFFER_SIZE * sizeof(lc_gcode_obj_t));

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

bool lc_planner_rb_insert(lc_planner_rb_t *rb, const lc_gcode_obj_t *gcode_obj)
{
    LC_ASSERT(&gcode_obj, "data pointer is NULL"); // Check if data is NULL

    if (rb->count == rb->size) // Check if the buffer is full
        return false;          // Return an error value

    rb->buffer[rb->head] = *gcode_obj;

    rb->head = (rb->head + 1) % rb->size;
    rb->count++; // Increment count

    return true;
}

bool lc_planner_rb_remove(lc_planner_rb_t *rb, lc_gcode_obj_t *gcode_obj)
{
    if (rb->count == 0)
        return false; // Return an error value

    *gcode_obj = rb->buffer[rb->tail];

    rb->tail = (rb->tail + 1) % rb->size;
    rb->count--; // Decrement count

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
