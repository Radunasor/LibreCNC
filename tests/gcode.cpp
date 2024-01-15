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

    LC_LOG_INFO("requested line is: %s", line_ptr[int_line_number]);

    *line_number = int_line_number++;

    if (!line_ptr[int_line_number])
        eof = true;

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
        gcode_cbs.lc_interface_gcode_get_end_of_file = lc_interface_gcode_get_enf_of_file;

        lc_gcode_init(&gcode_cbs);
    }

    void TearDown() override
    {
        lc_gcode_deinit();
    }

    static void ParsedGcodeCallback(const lc_gcode_obj_t *parsed_gcode)
    {
        LC_LOG_INFO("Gcode command %c parsed with Command %d%s",
                    lc_gcode_command_type_to_chr(parsed_gcode->command_type),
                    parsed_gcode->command_number,
                    parsed_gcode->subcommand_existed ? (" and subcommand " + std::to_string(parsed_gcode->sub_command_number)).c_str() : "");

        std::vector<std::pair<const char, lc_gcode_attr_t>> parsed_gcode_tag_map = {
            {'X', parsed_gcode->command_values.X},
            {'Y', parsed_gcode->command_values.Y},
            {'Z', parsed_gcode->command_values.Z},
            {'I', parsed_gcode->command_values.I},
            {'J', parsed_gcode->command_values.J},
            {'K', parsed_gcode->command_values.K},
            {'L', parsed_gcode->command_values.L},
            {'N', parsed_gcode->command_values.N},
            {'P', parsed_gcode->command_values.P},
            {'R', parsed_gcode->command_values.R},
            {'S', parsed_gcode->command_values.S},
            {'T', parsed_gcode->command_values.T},
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
    lc_gcode_set_parse_callback(ParsedGcodeCallback);

    while (!lc_interface_gcode_get_enf_of_file())
    {
        LC_LOG_INFO("********************************************************************");
        if (!lc_gcode_process_line())
            LC_LOG_ERROR("GCODE module couldn't parse last line, need to take some action");
    }
}