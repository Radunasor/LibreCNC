#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "data_structures/map/map.h"
}

std::vector<std::map<const char *, int>> test_data = {
    {{"one", 1},
     {"two", 2},
     {"three", 3},
     {"four", 4},
     {"five", 5},
     {"six", 6},
     {"seven", 7}},
};

class LCMap : public ::testing::TestWithParam<std::map<const char *, int>>
{
protected:
    void SetUp() override
    {
        lcmap = lc_map_create();
    }

    void TearDown() override
    {
        lc_map_destroy(lcmap);
    }

    std::map<const char *, int> convert_lcmap_to_stdmap()
    {
        std::map<const char *, int> stdmap = GetParam();
        std::map<const char *, int> converted_stdmap;

        for (std::map<const char *, int>::iterator mp_it = stdmap.begin(); mp_it != stdmap.end(); ++mp_it)
        {
            int *output = NULL;
            size_t output_size = 0;

            if (lc_map_find(lcmap, (void *)mp_it->first, strlen(mp_it->first), (void **)&output, &output_size))
                converted_stdmap.insert({mp_it->first, *output});
        }

        return converted_stdmap;
    }

    lc_map_t *lcmap;
};

TEST_P(LCMap, insert)
{
    std::map<const char *, int> expected = GetParam();

    for (std::map<const char *, int>::iterator mp_it = expected.begin(); mp_it != expected.end(); ++mp_it)
        lc_map_insert(lcmap, (void *)mp_it->first, strlen(mp_it->first), &mp_it->second, sizeof(mp_it->second));

    std::map<const char *, int> convertd_stdmap = convert_lcmap_to_stdmap();

    EXPECT_THAT(convertd_stdmap, ::testing::UnorderedElementsAreArray(expected.begin(), expected.end()));

    int overwrite_int = -1;
    size_t pair_no = expected.size() / 2;
    std::map<const char *, int>::iterator mp_it = expected.begin();
    std::advance(mp_it, pair_no);
    lc_map_insert(lcmap, (void *)mp_it->first, strlen(mp_it->first), &overwrite_int, sizeof(overwrite_int));

    convertd_stdmap.insert({mp_it->first, overwrite_int});

    EXPECT_THAT(convertd_stdmap, ::testing::UnorderedElementsAreArray(expected.begin(), expected.end()));
}

TEST_P(LCMap, find)
{
    std::map<const char *, int> expected = GetParam();

    for (std::map<const char *, int>::iterator mp_it = expected.begin(); mp_it != expected.end(); ++mp_it)
        lc_map_insert(lcmap, (void *)mp_it->first, strlen(mp_it->first), &mp_it->second, sizeof(mp_it->second));

    size_t pair_no = expected.size() / 2;
    std::map<const char *, int>::iterator mp_it = expected.begin();
    std::advance(mp_it, pair_no);

    int *output = NULL;
    size_t output_size = 0;

    EXPECT_TRUE(lc_map_find(lcmap, (void *)mp_it->first, strlen(mp_it->first), (void **)&output, &output_size));

    auto expected_output = expected.find(mp_it->first);

    EXPECT_EQ(*output, expected_output->second);
}

TEST_P(LCMap, erase)
{
    std::map<const char *, int> expected = GetParam();

    for (std::map<const char *, int>::iterator mp_it = expected.begin(); mp_it != expected.end(); ++mp_it)
        lc_map_insert(lcmap, (void *)mp_it->first, strlen(mp_it->first), &mp_it->second, sizeof(mp_it->second));

    size_t pair_no = expected.size() / 2;
    std::map<const char *, int>::iterator mp_it = expected.begin();
    std::advance(mp_it, pair_no);
    expected.erase(mp_it);

    lc_map_erase(lcmap, (void *)mp_it->first, strlen(mp_it->first));

    std::map<const char *, int> convertd_stdmap = convert_lcmap_to_stdmap();

    EXPECT_THAT(convertd_stdmap, ::testing::UnorderedElementsAreArray(expected.begin(), expected.end()));
}

TEST_P(LCMap, get_size)
{
    std::map<const char *, int> expected = GetParam();

    for (std::map<const char *, int>::iterator mp_it = expected.begin(); mp_it != expected.end(); ++mp_it)
        lc_map_insert(lcmap, (void *)mp_it->first, strlen(mp_it->first), &mp_it->second, sizeof(mp_it->second));

    size_t pair_no = expected.size() / 2;
    std::map<const char *, int>::iterator mp_it = expected.begin();
    std::advance(mp_it, pair_no);
    expected.erase(mp_it);

    lc_map_erase(lcmap, (void *)mp_it->first, strlen(mp_it->first));

    EXPECT_EQ(lc_map_get_size(lcmap), expected.size());
}

TEST_P(LCMap, clear)
{
    std::map<const char *, int> expected = GetParam();

    expected.clear();

    lc_map_clear(lcmap);

    EXPECT_EQ(lc_map_get_size(lcmap), expected.size());
}

INSTANTIATE_TEST_SUITE_P(map_data_driven_test, LCMap, testing::ValuesIn(test_data));