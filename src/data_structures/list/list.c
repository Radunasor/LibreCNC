#include "list.h"

typedef struct _lc_list_node_t lc_list_node_t;

struct
{
    void *data;
    lc_list_node_t *next;
    lc_list_node_t *prev;
} _lc_list_node_t;

struct
{
    lc_list_node_t *head;
    lc_list_node_t *tail;

    lc_list_node_t *current_node;
    size_t list_size;
} _lc_list_t;

tp_list_t *lc_list_create()
{
}

void lc_list_destroy(tp_list_t *list)
{
}

void lc_list_insert_front(tp_list_t *list, void *data)
{
}

void lc_list_insert_back(tp_list_t *list, void *data)
{
}

void lc_list_insert_at(tp_list_t *list, size_t index, void *data)
{
}

void *lc_list_pop_front(tp_list_t *list)
{
}

void *lc_list_pop_back(tp_list_t *list)
{
}

void *lc_list_pop_at(tp_list_t *list, size_t index)
{
}

void lc_list_clear(tp_list_t *list)
{
}

void lc_list_iterate(tp_list_t *list, lc_list_iterate_cb_t iter_cb)
{
}

bool lc_list_find(tp_list_t *list, void *data)
{
}

size_t lc_list_get_size(tp_list_t *list)
{
}
