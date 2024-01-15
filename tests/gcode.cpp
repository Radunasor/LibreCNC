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

bool lc_interface_gcode_get_line(char *line, size_t *line_number)
{
    static int int_line_number = 0;
    const char *line_ptr[] = {
        "G1 G5.12 G2.1 X5 YA Z7 T9 F1000 M123",
        "G2.1 G10.1 G100.0 X5000 Y12345 Z1.12345 T15 F500000 M100.100",
        ";G1 X10 Y10 ; this line should be ignored!",
        "G1 F50 ; these values should be ignored: G200 F100",
        NULL,
    };

    if (!line_ptr[int_line_number])
        return false;

    memcpy(line, line_ptr[int_line_number], strlen(line_ptr[int_line_number]));

    LC_LOG_INFO("requested line is: %s", line_ptr[int_line_number]);

    *line_number = int_line_number++;

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

    static void ParsedGcodeCallback(const lc_gcode_obj_t *parsed_gcode)
    {
        LC_LOG_INFO("Gcode command %c parsed with Command %d%s",
                     lc_gcode_command_type_to_chr(parsed_gcode->command_type),
                     parsed_gcode->command_number,
                     parsed_gcode->subcommand_existed ? (" and subcommand " + std::to_string(parsed_gcode->sub_command_number)).c_str() : "");
        
        lc_gcode_attrbute_value_t parsed_gcode_values = parsed_gcode->command_values;

        struct lc_gcode_parse_tag_map
        {
            const char tag;
            lc_gcode_attr_t *attr;
        } parsed_gcode_tag_map[] = {
            {'X', &parsed_gcode_values.X},
            {'Y', &parsed_gcode_values.Y},
            {'Z', &parsed_gcode_values.Z},
            {'I', &parsed_gcode_values.I},
            {'J', &parsed_gcode_values.J},
            {'K', &parsed_gcode_values.K},
            {'L', &parsed_gcode_values.L},
            {'N', &parsed_gcode_values.N},
            {'P', &parsed_gcode_values.P},
            {'R', &parsed_gcode_values.R},
            {'S', &parsed_gcode_values.S},
            {'T', &parsed_gcode_values.T},

            {'\0', NULL},
        };

        for (uint8_t i = 0; parsed_gcode_tag_map[i].tag; i++)
            if(parsed_gcode_tag_map[i].attr->existed)
                LC_LOG_INFO("%c=%f", parsed_gcode_tag_map[i].tag, parsed_gcode_tag_map[i].attr->value);
    }
};

TEST_F(LCGcode, initial_t)
{
    lc_gcode_set_parse_callback(ParsedGcodeCallback);

    while (lc_gcode_process_line())
        ;
}