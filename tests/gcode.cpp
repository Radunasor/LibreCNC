#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "gcode/gcode.h"
}

bool lc_interface_gcode_init()
{
    return true;
}

bool lc_interface_gcode_deinit()
{
    return true;
}

static int ln_number = 0;
bool lc_interface_gcode_get_line(char *line, size_t *line_number)
{
    const char *line_ptr = "G126.361 X5 Y6 Z7 T9 F1000 M123 \n";
    *line_number = ln_number++;
    memcpy(line, line_ptr, strlen(line_ptr));

    return true;
}

class LCGcode : public ::testing::Test
{
protected:
    void SetUp() override
    {
        static lc_interface_gcode_t gcode_cbs;
        gcode_cbs.lc_interface_gcode_deinit = lc_interface_gcode_deinit;
        gcode_cbs.lc_interface_gcode_init = lc_interface_gcode_init;
        gcode_cbs.lc_interface_gcode_get_line = lc_interface_gcode_get_line;

        lc_gcode_init(&gcode_cbs);
    }

    void TearDown() override
    {
        lc_gcode_deinit();
    }
};

TEST_F(LCGcode, initial_t)
{

    lc_gcode_set_callback(LC_GCODE_TYPE_G, [](uint16_t code, uint16_t subcode, lc_gcode_attrbute_value_t *values) {});
    lc_gcode_set_callback(LC_GCODE_TYPE_F, [](uint16_t code, uint16_t subcode, lc_gcode_attrbute_value_t *values) {});
    lc_gcode_set_callback(LC_GCODE_TYPE_M, [](uint16_t code, uint16_t subcode, lc_gcode_attrbute_value_t *values) {});

    lc_gcode_process_line();
}