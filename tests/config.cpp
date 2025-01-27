#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "config/config.h"
}

enum
{
    LC_CONFIG_TEST_KEY_1 = LC_CONFIG_KEY_LAST + 1,
    LC_CONFIG_TEST_KEY_2,
    LC_CONFIG_TEST_KEY_3,
    LC_CONFIG_TEST_KEY_4,
    LC_CONFIG_TEST_KEY_5,
    LC_CONFIG_TEST_KEY_6,
    LC_CONFIG_TEST_KEY_7,
    LC_CONFIG_TEST_KEY_8,
    LC_CONFIG_TEST_KEY_9,
};

class LCConfig : public ::testing::Test
{
protected:
    void SetUp() override
    {
        lc_config_init();
    }

    void TearDown() override
    {
        lc_config_deinit();
    }
};

TEST_F(LCConfig, set_get_bool)
{

    bool t1 = true;
    bool t2 = false;

    lc_config_set_bool(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), t1);
    lc_config_set_bool(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), t2);

    bool t_r = false;
    bool res = lc_config_get_bool(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), &t_r);

    EXPECT_TRUE(res);
    EXPECT_EQ(t1, t_r);

    res = lc_config_get_bool(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), &t_r);

    EXPECT_TRUE(res);
    EXPECT_EQ(t2, t_r);

    res = lc_config_get_bool(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_3), &t_r);
    EXPECT_FALSE(res);
}

TEST_F(LCConfig, set_get_int)
{

    int t1 = 123;
    int t2 = 321;

    lc_config_set_int(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), t1);
    lc_config_set_int(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), t2);

    int t_r = false;
    bool res = lc_config_get_int(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), &t_r);

    EXPECT_TRUE(res);
    EXPECT_EQ(t1, t_r);

    res = lc_config_get_int(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), &t_r);

    EXPECT_TRUE(res);
    EXPECT_EQ(t2, t_r);

    res = lc_config_get_int(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_3), &t_r);
    EXPECT_FALSE(res);
}

TEST_F(LCConfig, set_get_float)
{

    float t1 = 123.123;
    float t2 = 321.321;

    lc_config_set_float(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), t1);
    lc_config_set_float(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), t2);

    float t_r = false;
    bool res = lc_config_get_float(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), &t_r);

    EXPECT_TRUE(res);
    EXPECT_EQ(t1, t_r);

    res = lc_config_get_float(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), &t_r);

    EXPECT_TRUE(res);
    EXPECT_EQ(t2, t_r);

    res = lc_config_get_float(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_3), &t_r);
    EXPECT_FALSE(res);
}

TEST_F(LCConfig, set_get_data)
{

    uint8_t t1[] = {0x1, 0x2, 0x3, 0x4, 0x5};
    uint8_t t2[] = {0x5, 0x4, 0x3, 0x3, 0x1};
    lc_config_set_data(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), t1, sizeof(t1));
    lc_config_set_data(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), t2, sizeof(t2));

    uint8_t *t_r = NULL;
    size_t t_r_size = 0;
    bool res = lc_config_get_data(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_1), &t_r, &t_r_size);

    EXPECT_TRUE(res);
    EXPECT_EQ(t_r_size, sizeof(t1));
    EXPECT_THAT(t1, ::testing::ElementsAreArray(t_r, t_r_size));

    res = lc_config_get_data(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_2), &t_r, &t_r_size);

    EXPECT_TRUE(res);
    EXPECT_EQ(t_r_size, sizeof(t2));
    EXPECT_THAT(t2, ::testing::ElementsAreArray(t_r, t_r_size));

    res = lc_config_get_data(LC_CONFIG_KEY_INT(LC_CONFIG_TEST_KEY_3), &t_r, &t_r_size);
    EXPECT_FALSE(res);
}

TEST_F(LCConfig, string_key_test)
{

    uint8_t t1[] = {0x1, 0x2, 0x3, 0x4, 0x5};
    uint8_t t2[] = {0x5, 0x4, 0x3, 0x3, 0x1};
    lc_config_set_data(LC_CONFIG_KEY_STRING("test1"), t1, sizeof(t1));
    lc_config_set_data(LC_CONFIG_KEY_STRING("test2"), t2, sizeof(t2));

    uint8_t *t_r = NULL;
    size_t t_r_size = 0;
    bool res = lc_config_get_data(LC_CONFIG_KEY_STRING("test1"), &t_r, &t_r_size);

    EXPECT_TRUE(res);
    EXPECT_EQ(t_r_size, sizeof(t1));
    EXPECT_THAT(t1, ::testing::ElementsAreArray(t_r, t_r_size));

    res = lc_config_get_data(LC_CONFIG_KEY_STRING("test2"), &t_r, &t_r_size);

    EXPECT_TRUE(res);
    EXPECT_EQ(t_r_size, sizeof(t2));
    EXPECT_THAT(t2, ::testing::ElementsAreArray(t_r, t_r_size));

    res = lc_config_get_data(LC_CONFIG_KEY_STRING("test3"), &t_r, &t_r_size);
    EXPECT_FALSE(res);
}