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

static void *lc_list_node_erase(lc_list_t *list, lc_list_node_t *node_to_erase)
{
    void *data = NULL;

    list->list_size -= 1;

    if (node_to_erase == list->head)
    {
        lc_list_node_t *ex_head = list->head;

        if (list->list_size > 1)
            ex_head->next->prev = NULL;

        list->head = ex_head->next;
        data = ex_head->data;

        _free(ex_head);

        return data;
    }

    if (node_to_erase == list->tail)
    {
        lc_list_node_t *ex_tail = list->tail;

        ex_tail->prev->next = NULL;
        list->tail = ex_tail->prev;
        data = ex_tail->data;

        _free(ex_tail);
        return data;
    }

    node_to_erase->prev->next = node_to_erase->next;
    node_to_erase->next->prev = node_to_erase->prev;
    data = node_to_erase->data;

    _free(node_to_erase);

    return data;
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

    if (current_node_at_idx != list->head)
        current_node_at_idx->prev->next = new_node;

    current_node_at_idx->prev = new_node;

    if (current_node_at_idx == list->head)
        list->head = new_node;

    list->list_size += 1;
}

void *lc_list_pop_front(lc_list_t *list)
{
    LC_ASSERT(list->list_size, "list pop front invalid size");

    return lc_list_node_erase(list, list->head);
}

void *lc_list_pop_back(lc_list_t *list)
{
    LC_ASSERT(list->list_size, "list pop back invalid size");

    return lc_list_node_erase(list, list->tail);
}

void *lc_list_pop_at(lc_list_t *list, size_t index)
{
    LC_ASSERT(index < list->list_size, "pop index out of range");

    return lc_list_node_erase(list, lc_list_get_node(list, index));
}

void lc_list_clear(lc_list_t *list)
{
    size_t initial_size = list->list_size;

    for (size_t i = 0; i < initial_size; i++)
        lc_list_pop_back(list);
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
    size_t tmp_idx = 0;

    LIST_INTERNAL_RANGELOOP(list, node)
    {
        if (data == node->data)
            return tmp_idx;

        tmp_idx++;
    }

    return -1;
}

size_t lc_list_get_size(lc_list_t *list)
{
    return list->list_size;
}
