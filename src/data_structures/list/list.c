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

lc_list_t *lc_list_create()
{
    lc_list_t *list = _malloc(sizeof(_lc_list_t));

    LC_ASSERT(list, "List create memory allocation returned NULL.");

    return list;
}

void lc_list_destroy(lc_list_t *list)
{
    _free(list);
}

void lc_list_insert_front(lc_list_t *list, void *data)
{
}

void lc_list_insert_back(lc_list_t *list, void *data)
{
}

void lc_list_insert_at(lc_list_t *list, size_t index, void *data)
{
}

void *lc_list_pop_front(lc_list_t *list)
{
}

void *lc_list_pop_back(lc_list_t *list)
{
}

void *lc_list_pop_at(lc_list_t *list, size_t index)
{
}

void lc_list_clear(lc_list_t *list)
{
}

void *lc_list_find_at(lc_list_t *list, size_t index)
{
}

void lc_list_foreach(lc_list_t *list, lc_list_iterate_cb_t iter_cb)
{
}

bool lc_list_find(lc_list_t *list, void *data)
{
}

size_t lc_list_get_size(lc_list_t *list)
{
}
