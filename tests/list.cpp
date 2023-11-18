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
    {VOID_PTR(6), VOID_PTR(5), VOID_PTR(4), VOID_PTR(3), VOID_PTR(2), VOID_PTR(1), VOID_PTR(0)},
    {VOID_PTR(1)},
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

    void convert_lclist_to_stdlist(std::list<void *> &stsdlist, lc_list_t *list)
    {
        void *data_ptr = NULL;
        LIST_FOREACH(list, data_ptr)
        stsdlist.push_back(data_ptr);
    }

    lc_list_t *lclist;
};

TEST_P(LCList, insert_front)
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

TEST_P(LCList, insert_back)
{
    std::list<void *> stdlist = GetParam();

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    std::list<void *> converted_lclist;
    convert_lclist_to_stdlist(converted_lclist, lclist);

    EXPECT_THAT(converted_lclist, testing::ElementsAreArray(stdlist));
}

TEST_P(LCList, insert_at)
{
    std::list<void *> stdlist = GetParam();

    if (stdlist.size() == 0) // temp solution!
    {
        EXPECT_TRUE(true);
        return;
    }

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    const size_t index = stdlist.size() / 2;

    auto index_it = stdlist.begin();
    std::advance(index_it, index);
    stdlist.insert(index_it, VOID_PTR("test data"));

    lc_list_insert_at(lclist, index, VOID_PTR("test data"));

    std::list<void *> converted_lclist;
    convert_lclist_to_stdlist(converted_lclist, lclist);

    EXPECT_EQ(index, lc_list_get_index(lclist, lc_list_find_at(lclist, index)));

    EXPECT_THAT(converted_lclist, testing::ElementsAreArray(stdlist));
}

TEST_P(LCList, pop_front)
{
    std::list<void *> stdlist = GetParam();

    if (stdlist.size() == 0) // temp solution!
    {
        EXPECT_TRUE(true);
        return;
    }

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    lc_list_pop_front(lclist);
    stdlist.pop_front();

    std::list<void *> converted_lclist;
    convert_lclist_to_stdlist(converted_lclist, lclist);

    EXPECT_THAT(converted_lclist, testing::ElementsAreArray(stdlist));
}

TEST_P(LCList, pop_back)
{
    std::list<void *> stdlist = GetParam();

    if (stdlist.size() == 0) // temp solution!
    {
        EXPECT_TRUE(true);
        return;
    }

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    lc_list_pop_back(lclist);
    stdlist.pop_back();

    std::list<void *> converted_lclist;
    convert_lclist_to_stdlist(converted_lclist, lclist);

    EXPECT_THAT(converted_lclist, testing::ElementsAreArray(stdlist));
}

TEST_P(LCList, pop_at)
{
    std::list<void *> stdlist = GetParam();

    if (stdlist.size() == 0) // temp solution!
    {
        EXPECT_TRUE(true);
        return;
    }

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    const size_t index = stdlist.size() / 2;

    lc_list_pop_at(lclist, index);

    auto index_it = stdlist.begin();
    std::advance(index_it, index);
    stdlist.erase(index_it);

    std::list<void *> converted_lclist;
    convert_lclist_to_stdlist(converted_lclist, lclist);

    EXPECT_THAT(converted_lclist, testing::ElementsAreArray(stdlist));
}

TEST_P(LCList, clear)
{
    std::list<void *> stdlist = GetParam();

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    lc_list_clear(lclist);
    stdlist.clear();

    std::list<void *> converted_lclist;
    convert_lclist_to_stdlist(converted_lclist, lclist);

    EXPECT_THAT(converted_lclist, testing::ElementsAreArray(stdlist));
}

TEST_P(LCList, find_at)
{
    std::list<void *> stdlist = GetParam();

    if (stdlist.size() == 0) // temp solution!
    {
        EXPECT_TRUE(true);
        return;
    }

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    const size_t index = stdlist.size() / 2;

    auto index_it = stdlist.begin();
    std::advance(index_it, index);

    EXPECT_EQ(lc_list_find_at(lclist, index), *index_it);
}

TEST_P(LCList, get_size)
{
    std::list<void *> stdlist = GetParam();

    for (void *n : stdlist)
        lc_list_insert_back(lclist, n);

    EXPECT_EQ(lc_list_get_size(lclist), stdlist.size());
}

INSTANTIATE_TEST_CASE_P(list_data_driven_test, LCList, testing::ValuesIn(test_data));