#include <list>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#define VOID_PTR(x) (void *)(x)
#include "data_structures/list/list.h"
}

std::list<std::list<void *>> test_data = {
    {VOID_PTR(1), VOID_PTR(2), VOID_PTR(3), VOID_PTR(4), VOID_PTR(5)},
    {VOID_PTR(6), VOID_PTR(5), VOID_PTR(4), VOID_PTR(3), VOID_PTR(2), VOID_PTR(1)},
    {},
};

class LCList : public ::testing::TestWithParam<std::list<void *>>
{
protected:
    void SetUp() override
    {
        lclist = lc_list_create();
    }

    void TearDown() override
    {
        lc_list_destroy(lclist);
    }

    void convert_lclist_to_stdlist(std::list<void *> &stdlist, lc_list_t *list)
    {
        void *data_ptr = NULL;
        LIST_FOREACH(list, data_ptr)
        stdlist.push_back(data_ptr);
    }

    lc_list_t *lclist;
};

TEST_P(LCList, InsertFront)
{
    std::list<void *> stdlist = GetParam();

    for (void *n : stdlist)
        lc_list_insert_front(lclist, n);

    std::list<void *> stdlist_r(stdlist.size());
    std::reverse_copy(stdlist.begin(), stdlist.end(), stdlist_r.begin());

    std::list<void *> converted_lclist;
    convert_lclist_to_stdlist(converted_lclist, lclist);

    EXPECT_THAT(converted_lclist, testing::ElementsAreArray(stdlist_r));
}

// void lc_list_insert_front(lc_list_t *list, void *data);
// void lc_list_insert_back(lc_list_t *list, void *data);
// void lc_list_insert_at(lc_list_t *list, size_t index, void *data);

// void *lc_list_pop_front(lc_list_t *list);
// void *lc_list_pop_back(lc_list_t *list);
// void *lc_list_pop_at(lc_list_t *list, size_t index);

// void lc_list_clear(lc_list_t *list);

// void *lc_list_find_at(lc_list_t *list, size_t index);

// size_t lc_list_get_index(lc_list_t *list, void *data);

// size_t lc_list_get_size(lc_list_t *list);

INSTANTIATE_TEST_CASE_P(list_data_driven_test, LCList, testing::ValuesIn(test_data));