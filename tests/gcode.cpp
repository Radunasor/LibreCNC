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
    const char *line_ptr = "G1 G5.12 G2.1 X5 Y6 Z7 T9 F1000 M123";
    *line_number = ln_number++;
    memcpy(line, line_ptr, strlen(line_ptr));

    LC_LOG_INFO("requested line is: %s", line_ptr);

    return true;
}

static const char lc_gcode_command_type_to_chr(lc_gcode_command_type_t command_type)
{
    char tag = 0;

    switch (command_type)
    {
    case LC_GCODE_TYPE_F:
        tag = 'F';
        break;
    case LC_GCODE_TYPE_M:
        tag = 'M';
        break;
    case LC_GCODE_TYPE_G:
        tag = 'G';
        break;
    default:
        break;
    }

    return tag;
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
    lc_gcode_set_parse_callback([](const lc_gcode_obj_t *parsed_gcode)
                                { LC_LOG_INFO("Gcode command %c parsed with Command %d%s",
                                              lc_gcode_command_type_to_chr(parsed_gcode->command_type),
                                              parsed_gcode->command_number,
                                              parsed_gcode->subcommand_existed ? (" and subcommand " + std::to_string(parsed_gcode->sub_command_number)).c_str() : "") });

    lc_gcode_process_line();
}