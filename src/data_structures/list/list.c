#include <string.h>

#include "list.h"

typedef struct _lc_list_node_t lc_list_node_t;

struct _lc_list_node_t
{
    void *data;
    lc_list_node_t *next;
    lc_list_node_t *prev;
};

struct _lc_list_t
{
    lc_list_node_t *head;
    lc_list_node_t *tail;

    size_t list_size;
};

#define LIST_INTERNAL_RANGELOOP(list, node) for (lc_list_node_t *node = list->head; node != NULL; node = node->next)

static lc_list_node_t *lc_list_get_node(lc_list_t *list, size_t index)
{
    LC_ASSERT(index < list->list_size, "list insert out of range");

    size_t tmp_idx = 0;
    lc_list_node_t *node_ptr = NULL;

    LIST_INTERNAL_RANGELOOP(list, node)
    {
        if (tmp_idx == index)
        {
            node_ptr = node;
            break;
        }
        tmp_idx++;
    }

    return node_ptr;
}

lc_list_t *lc_list_create()
{
    lc_list_t *list = _malloc(sizeof(lc_list_t));

    LC_ASSERT(list, "List memory allocation returned NULL.");

    memset(list, 0, sizeof(lc_list_t));

    return list;
}

void lc_list_destroy(lc_list_t *list)
{
    _free(list);
}

void lc_list_insert_front(lc_list_t *list, void *data)
{
    lc_list_node_t *new_node = _malloc(sizeof(lc_list_node_t));

    LC_ASSERT(new_node, "List Node memory allocation returned NULL.");

    memset(new_node, 0, sizeof(lc_list_node_t));

    new_node->data = data;

    if (list->head)
    {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    else
    {
        list->head = new_node;
        list->tail = new_node;
    }

    list->list_size += 1;
}

void lc_list_insert_back(lc_list_t *list, void *data)
{
    lc_list_node_t *new_node = _malloc(sizeof(lc_list_node_t));

    LC_ASSERT(new_node, "List Node memory allocation returned NULL.");

    memset(new_node, 0, sizeof(lc_list_node_t));

    new_node->data = data;

    if (list->tail)
    {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    else
    {
        list->head = new_node;
        list->tail = new_node;
    }

    list->list_size += 1;
}

void lc_list_insert_at(lc_list_t *list, size_t index, void *data)
{
    LC_ASSERT(index < list->list_size, "list insert out of range");

    lc_list_node_t *new_node = _malloc(sizeof(lc_list_node_t));

    LC_ASSERT(new_node, "List Node memory allocation returned NULL.");

    memset(new_node, 0, sizeof(lc_list_node_t));

    new_node->data = data;

    lc_list_node_t *current_node_at_idx = lc_list_get_node(list, index);

    new_node->next = current_node_at_idx;
    new_node->prev = current_node_at_idx->prev;
    current_node_at_idx->prev->next = new_node;
    current_node_at_idx->prev = new_node;

    if (index == 0)
        list->head = new_node;

    if (index == list->list_size - 1)
        list->tail = new_node;

    list->list_size += 1;
}

void *lc_list_pop_front(lc_list_t *list)
{
    void *data = NULL;

    if (list->list_size == 0)
        return data;

    if (list->list_size == 1)
    {
        data = list->head->data;

        _free(list->head);

        list->head = NULL;
        list->tail = NULL;

        list->list_size = 0;

        return data;
    }

    lc_list_node_t *ex_head = list->head;
    data = ex_head->data;
    list->head = list->head->next;
    list->head->prev = NULL;

    _free(ex_head);

    list->list_size -= 1;

    return data;
}

void *lc_list_pop_back(lc_list_t *list)
{
    void *data = NULL;

    if (list->list_size == 0)
        return data;

    if (list->list_size == 1)
    {
        data = list->head->data;

        _free(list->head);

        list->head = NULL;
        list->tail = NULL;

        list->list_size = 0;

        return data;
    }

    lc_list_node_t *ex_tail = list->tail;
    data = ex_tail->data;
    list->tail = list->tail->prev;
    list->tail->next = NULL;

    _free(ex_tail);

    list->list_size -= 1;

    return data;
}

void *lc_list_pop_at(lc_list_t *list, size_t index)
{
    LC_ASSERT(index < list->list_size, "list insert out of range");

    void *data = NULL;

    lc_list_node_t *target_node = lc_list_find_at(list, index);

    if (!target_node)
        return data;

    data = target_node->data;
    target_node->prev->next = target_node->next;
    target_node->next->prev = target_node->prev;

    _free(target_node);

    list->list_size -= 1;

    return data;
}

void lc_list_clear(lc_list_t *list)
{
    while (lc_list_pop_back(list))
        ;
}

void *lc_list_find_at(lc_list_t *list, size_t index)
{
    LC_ASSERT(index < list->list_size, "list insert out of range");

    size_t tmp_idx = 0;

    LIST_INTERNAL_RANGELOOP(list, node)
    {
        if (tmp_idx == index)
            return node->data;

        tmp_idx++;
    }

    return NULL;
}

size_t lc_list_get_index(lc_list_t *list, void *data)
{
    size_t tmp_idx = -1;

    LIST_INTERNAL_RANGELOOP(list, node)
    {
        if (data == node->data)
            return tmp_idx;

        tmp_idx++;
    }

    return tmp_idx;
}

size_t lc_list_get_size(lc_list_t *list)
{
    return list->list_size;
}
