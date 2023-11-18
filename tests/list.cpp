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
        stdlist.push_front(data_ptr);
    }

    lc_list_t *lclist;
};

TEST_P(LCList, InsertFront)
{
    std::list<void *> stdlist = GetParam();

    for (void *n : stdlist)
        lc_list_insert_front(lclist, n);

    std::list<void *> lclist_elements;
    convert_lclist_to_stdlist(lclist_elements, lclist);

    EXPECT_THAT(lclist_elements, testing::ElementsAreArray(stdlist));
}

INSTANTIATE_TEST_CASE_P(list_data_driven_test, LCList, testing::ValuesIn(test_data));