#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "data_structures/ring_buffer/ring_buffer.h"
}
class RingBufferTest : public ::testing::Test
{
protected:
    lc_ring_buffer_t *rb;

    void SetUp() override
    {
        rb = lc_ring_buffer_create(10);
    }

    void TearDown() override
    {
        lc_ring_buffer_destroy(rb);
    }
};

TEST_F(RingBufferTest, CreateDestroy)
{
    EXPECT_NE(rb, nullptr);
}

TEST_F(RingBufferTest, InsertRemove)
{
    int data1 = 123;
    lc_ring_buffer_insert(rb, &data1);
    int *data2 = (int *)lc_ring_buffer_remove(rb);
    EXPECT_EQ(*data2, 123);
}

TEST_F(RingBufferTest, BufferFull)
{
    for (int i = 0; i < 10; i++)
        lc_ring_buffer_insert(rb, &i);

    int data = 999;
    lc_ring_buffer_insert(rb, &data);
    int *removed_data = (int *)lc_ring_buffer_remove(rb);
    EXPECT_EQ(removed_data, nullptr); // The new data should not be in the buffer
}

TEST_F(RingBufferTest, BufferEmpty)
{
    EXPECT_EQ(lc_ring_buffer_remove(rb), nullptr);
}