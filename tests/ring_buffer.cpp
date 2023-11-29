#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "data_structures/ring_buffer/ring_buffer.h"
}
class RingBuffer : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialization code, executed before each test
        rb = lc_ring_buffer_create(3); // Change the size as needed
    }

    void TearDown() override
    {
        // Clean-up code, executed after each test
        lc_ring_buffer_destroy(rb);
    }

    lc_ring_buffer_t *rb;
};

TEST_F(RingBuffer, Creation)
{
    ASSERT_NE(rb, nullptr);
    EXPECT_EQ(lc_ring_buffer_get_elemets_count(rb), 0);
    EXPECT_EQ(lc_ring_buffer_get_size(rb), 3); // Change the size as needed
    EXPECT_FALSE(lc_ring_buffer_is_full(rb));
}

TEST_F(RingBuffer, InsertionAndRemoval)
{
    // Insert elements
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    lc_ring_buffer_insert(rb, &data1);
    lc_ring_buffer_insert(rb, &data2);
    lc_ring_buffer_insert(rb, &data3);

    EXPECT_EQ(lc_ring_buffer_get_elemets_count(rb), 3);
    EXPECT_TRUE(lc_ring_buffer_is_full(rb));

    // Remove elements
    int *removed1 = (int *)lc_ring_buffer_remove(rb);
    int *removed2 = (int *)lc_ring_buffer_remove(rb);
    int *removed3 = (int *)lc_ring_buffer_remove(rb);

    EXPECT_EQ(*removed1, 1);
    EXPECT_EQ(*removed2, 2);
    EXPECT_EQ(*removed3, 3);

    EXPECT_EQ(lc_ring_buffer_get_elemets_count(rb), 0);
    EXPECT_FALSE(lc_ring_buffer_is_full(rb));
}

TEST_F(RingBuffer, InsertionWhenFull)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;

    lc_ring_buffer_insert(rb, &data1);
    lc_ring_buffer_insert(rb, &data2);
    lc_ring_buffer_insert(rb, &data3);

    EXPECT_TRUE(lc_ring_buffer_is_full(rb));

    // Try to insert when full
    lc_ring_buffer_insert(rb, &data4);

    EXPECT_EQ(lc_ring_buffer_get_elemets_count(rb), 3);
    EXPECT_TRUE(lc_ring_buffer_is_full(rb));
}

TEST_F(RingBuffer, RemovalWhenEmpty)
{
    // Try to remove from an empty buffer
    int *removed = (int *)lc_ring_buffer_remove(rb);

    EXPECT_EQ(removed, nullptr);
}
