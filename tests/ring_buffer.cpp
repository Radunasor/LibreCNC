#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "gcode/gcode.h" 
#include "planner/ring_buffer.h"
}

class LCPlannerRB : public ::testing::Test
{
protected:
    lc_planner_rb_t *mRinfBuffer;

    void SetUp() override
    {
        mRinfBuffer = lc_planner_rb_create();
    }

    void TearDown() override
    {
        lc_planner_rb_destroy(mRinfBuffer);
        mRinfBuffer = nullptr;
    }
};

TEST_F(LCPlannerRB, insert_remove)
{
    lc_gcode_obj_t base_gcode_obj;
    memset(&base_gcode_obj, 0, sizeof(lc_gcode_obj_t));
    base_gcode_obj.command_type = LC_GCODE_TYPE_F;
    base_gcode_obj.command_number = 100;
    base_gcode_obj.subcommand_existed = false;
    base_gcode_obj.sub_command_number = 0;

    lc_gcode_g_command_t g_command_obj;
    memset(&g_command_obj, 0, sizeof(lc_gcode_g_command_t));
    g_command_obj.command.command_type = LC_GCODE_TYPE_G;
    g_command_obj.command.command_number = 1;
    g_command_obj.command.subcommand_existed = false;
    g_command_obj.command.sub_command_number = 0;
    g_command_obj.X = {.existed = true, .value = 123};
    g_command_obj.Y = {.existed = true, .value = 321};

    lc_gcode_m_command_t m_command_obj;
    memset(&m_command_obj, 0, sizeof(lc_gcode_m_command_t));
    m_command_obj.command.command_type = LC_GCODE_TYPE_M;
    m_command_obj.command.command_number = 100;
    m_command_obj.command.subcommand_existed = false;
    m_command_obj.command.sub_command_number = 0;
    m_command_obj.E = {.existed = true, .value = 123};
    m_command_obj.R = {.existed = true, .value = 321};

    EXPECT_EQ(lc_planner_rb_insert(mRinfBuffer, &base_gcode_obj), true);
    EXPECT_EQ(lc_planner_rb_insert(mRinfBuffer, (lc_gcode_obj_t *)&g_command_obj), true);
    EXPECT_EQ(lc_planner_rb_insert(mRinfBuffer, (lc_gcode_obj_t *)&m_command_obj), true);

    for(uint8_t element=0; element <= LC_PLANNER_GCODE_RB_BUFFER_SIZE - 4; element++)
        EXPECT_EQ(lc_planner_rb_insert(mRinfBuffer, (lc_gcode_obj_t *)&m_command_obj), true);

    // ring buffer is full
    EXPECT_EQ(lc_planner_rb_insert(mRinfBuffer, (lc_gcode_obj_t *)&m_command_obj), false);

    lc_gcode_obj_t rb_f_command;
    lc_planner_rb_remove(mRinfBuffer, &rb_f_command);
    EXPECT_EQ(memcmp(&rb_f_command, &base_gcode_obj, sizeof(lc_gcode_obj_t)), 0);

    lc_gcode_g_command_t rb_g_command;
    lc_planner_rb_remove(mRinfBuffer, (lc_gcode_obj_t *) &rb_g_command);
    EXPECT_EQ(memcmp(&rb_g_command, &g_command_obj, sizeof(lc_gcode_g_command_t)), 0);

    lc_gcode_m_command_t rb_m_command;
    lc_planner_rb_remove(mRinfBuffer, (lc_gcode_obj_t *) &rb_m_command);
    EXPECT_EQ(memcmp(&rb_m_command, &m_command_obj, sizeof(lc_gcode_m_command_t)), 0);

    EXPECT_EQ(lc_planner_rb_insert(mRinfBuffer, (lc_gcode_obj_t *)&base_gcode_obj), true);
}