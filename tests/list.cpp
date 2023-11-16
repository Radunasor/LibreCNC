#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "data_structures/list/list.h"
}

TEST(List, InsertFront)
{

    lc_list_t *mp_list = lc_list_create();

    int i = 5;

    lc_list_insert_front(mp_list, &i);
    int *j = (int *)lc_list_find_at(mp_list, 0);

    EXPECT_TRUE(i == *j);
}