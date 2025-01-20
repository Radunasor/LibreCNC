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

static bool eof = false;
bool lc_interface_gcode_get_enf_of_file()
{
    return eof;
}

bool lc_interface_gcode_get_line(char *line, size_t *line_number)
{
    static int int_line_number = 0;
    const char *line_ptr[] = {
        "G1 G5.12 G2.1 X5 Y10 Z7 T9 F1000 M123",
        "G2.1 G10.1 G100.0 X5000 Y12345 Z1.12345 T15 F500000 M100.100",
        "F1000",
        "M99",
        "G82",
        ";G1 X10 Y10 ; this line should be ignored!",
        "G1 F50 ; these values should be ignored => G200 F100",
        "G1 F50 Xa Y10 Z15 ; this line has syntax error in it, should cause parse error",
        NULL,
    };

    memcpy(line, line_ptr[int_line_number], strlen(line_ptr[int_line_number]));

    *line_number = ++int_line_number;

    if (!line_ptr[int_line_number])
        eof = true;

    return true;
}

class LCGcode : public ::testing::Test
{
protected:
    void SetUp() override
    {
        lc_gcode_init();
    }

    void TearDown() override
    {
        lc_gcode_deinit();
    }

    static void gCommandHandlerCallback(const lc_gcode_obj_t *parsed_gcode)
    {
        LC_LOG_INFO("Gcode command %c parsed with Command %d%s",
                    lc_gcode_get_command_type(parsed_gcode),
                    lc_gcode_get_command_number(parsed_gcode),
                    lc_gcode_get_sub_command_existed(parsed_gcode) ? (" and subcommand " + std::to_string(lc_gcode_get_sub_command_number(parsed_gcode))).c_str() : "");

        std::vector<std::pair<const char, lc_gcode_g_command_attr_t>> parsed_gcode_tag_map = {
            {'X', ((lc_gcode_g_command_t *)parsed_gcode)->X},
            {'Y', ((lc_gcode_g_command_t *)parsed_gcode)->Y},
            {'Z', ((lc_gcode_g_command_t *)parsed_gcode)->Z},
            {'I', ((lc_gcode_g_command_t *)parsed_gcode)->I},
            {'J', ((lc_gcode_g_command_t *)parsed_gcode)->J},
            {'K', ((lc_gcode_g_command_t *)parsed_gcode)->K},
            {'L', ((lc_gcode_g_command_t *)parsed_gcode)->L},
            {'N', ((lc_gcode_g_command_t *)parsed_gcode)->N},
            {'P', ((lc_gcode_g_command_t *)parsed_gcode)->P},
            {'R', ((lc_gcode_g_command_t *)parsed_gcode)->R},
            {'S', ((lc_gcode_g_command_t *)parsed_gcode)->S},
            {'T', ((lc_gcode_g_command_t *)parsed_gcode)->T},
            };

        for (auto pair : parsed_gcode_tag_map)
        {
            if (pair.second.existed)
                LC_LOG_INFO("%c=%f", pair.first, pair.second.value);
        }
    }

    static void mCommandHandlerCallback(const lc_gcode_obj_t *parsed_gcode)
    {
        LC_LOG_INFO("Gcode command %c parsed with Command %d%s",
                    lc_gcode_get_command_type(parsed_gcode),
                    lc_gcode_get_command_number(parsed_gcode),
                    lc_gcode_get_sub_command_existed(parsed_gcode) ? (" and subcommand " + std::to_string(lc_gcode_get_sub_command_number(parsed_gcode))).c_str() : "");

        std::vector<std::pair<const char, lc_gcode_m_command_attr_t>> parsed_gcode_tag_map = {
            {'R', ((lc_gcode_m_command_t *)parsed_gcode)->R},
            {'Q', ((lc_gcode_m_command_t *)parsed_gcode)->Q},
            {'P', ((lc_gcode_m_command_t *)parsed_gcode)->P},
            {'E', ((lc_gcode_m_command_t *)parsed_gcode)->E},
            {'L', ((lc_gcode_m_command_t *)parsed_gcode)->L}
            };

        for (auto pair : parsed_gcode_tag_map)
        {
            if (pair.second.existed)
                LC_LOG_INFO("%c=%f", pair.first, pair.second.value);
        }
    }
};

TEST_F(LCGcode, initial_t)
{
    lc_gcode_g_command_set_handler_callback(gCommandHandlerCallback);
    lc_gcode_m_command_set_handler_callback(mCommandHandlerCallback);

    while (!lc_interface_gcode_get_enf_of_file())
    {
        char line[LC_GCODE_MAX_LINE_LENTGH] = {0};
        size_t line_num = 0;
        lc_interface_gcode_get_line(line, &line_num);
        LC_LOG_INFO("********************************************************************");
        LC_LOG_INFO("<<requested line is: %s>>", line);
        if (!lc_gcode_process_line((const char *)line, line_num))
            LC_LOG_ERROR("GCODE module couldn't parse last line, need to take some action");
    }
}