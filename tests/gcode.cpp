#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "gcode/gcode.h"
#include "config/config.h"
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
        "M103 R15.1 Q40 P100000 E12 L13",
        "M99",
        "G82",
        "G01 X-1.23 Y-2.10 Z-3.21 ; test negative numbers",
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
        #ifdef LC_GCODE_PARAMETER_SUPPORT
        lc_config_init();
        #endif
        lc_gcode_init();
    }

    void TearDown() override
    {
        #ifdef LC_GCODE_PARAMETER_SUPPORT
        lc_config_deinit();
        #endif
        lc_gcode_deinit();
    }

    static std::vector<std::pair<const char, lc_gcode_command_attr_t>> g_command_attr_map_create(const lc_gcode_obj_t *parsed_gcode)
    {
        float X_value = 0;
        bool X_existed = lc_gcode_g_command_get_attr_X(parsed_gcode, &X_value);

        float Y_value = 0;
        bool Y_existed = lc_gcode_g_command_get_attr_Y(parsed_gcode, &Y_value);

        float Z_value = 0;
        bool Z_existed = lc_gcode_g_command_get_attr_Z(parsed_gcode, &Z_value);

        float I_value = 0;
        bool I_existed = lc_gcode_g_command_get_attr_I(parsed_gcode, &I_value);

        float J_value = 0;
        bool J_existed = lc_gcode_g_command_get_attr_J(parsed_gcode, &J_value);

        float K_value = 0;
        bool K_existed = lc_gcode_g_command_get_attr_K(parsed_gcode, &K_value);

        float L_value = 0;
        bool L_existed = lc_gcode_g_command_get_attr_L(parsed_gcode, &L_value);

        float N_value = 0;
        bool N_existed = lc_gcode_g_command_get_attr_N(parsed_gcode, &N_value);

        float P_value = 0;
        bool P_existed = lc_gcode_g_command_get_attr_P(parsed_gcode, &P_value);

        float R_value = 0;
        bool R_existed = lc_gcode_g_command_get_attr_R(parsed_gcode, &R_value);

        float S_value = 0;
        bool S_existed = lc_gcode_g_command_get_attr_S(parsed_gcode, &S_value);

        float T_value = 0;
        bool T_existed = lc_gcode_g_command_get_attr_T(parsed_gcode, &T_value);

        std::vector<std::pair<const char, lc_gcode_command_attr_t>> parsed_gcode_tag_map = {
            {'X', (lc_gcode_command_attr_t){X_existed, X_value}},
            {'Y', (lc_gcode_command_attr_t){Y_existed, Y_value}},
            {'Z', (lc_gcode_command_attr_t){Z_existed, Z_value}},
            {'I', (lc_gcode_command_attr_t){I_existed, I_value}},
            {'J', (lc_gcode_command_attr_t){J_existed, J_value}},
            {'K', (lc_gcode_command_attr_t){K_existed, K_value}},
            {'L', (lc_gcode_command_attr_t){L_existed, L_value}},
            {'N', (lc_gcode_command_attr_t){N_existed, N_value}},
            {'P', (lc_gcode_command_attr_t){P_existed, P_value}},
            {'R', (lc_gcode_command_attr_t){R_existed, R_value}},
            {'S', (lc_gcode_command_attr_t){S_existed, S_value}},
            {'T', (lc_gcode_command_attr_t){T_existed, T_value}},
        };

        return parsed_gcode_tag_map;
    }

    static std::vector<std::pair<const char, lc_gcode_command_attr_t>> m_command_attr_map_create(const lc_gcode_obj_t *parsed_gcode)
    {
        float R_value = 0;
        bool R_existed = lc_gcode_m_command_get_attr_R(parsed_gcode, &R_value);

        float Q_value = 0;
        bool Q_existed = lc_gcode_m_command_get_attr_Q(parsed_gcode, &Q_value);

        float P_value = 0;
        bool P_existed = lc_gcode_m_command_get_attr_P(parsed_gcode, &P_value);

        float E_value = 0;
        bool E_existed = lc_gcode_m_command_get_attr_E(parsed_gcode, &E_value);

        float L_value = 0;
        bool L_existed = lc_gcode_m_command_get_attr_L(parsed_gcode, &L_value);

        std::vector<std::pair<const char, lc_gcode_command_attr_t>> parsed_gcode_tag_map = {
            {'R', (lc_gcode_command_attr_t){R_existed, R_value}},
            {'Q', (lc_gcode_command_attr_t){Q_existed, Q_value}},
            {'P', (lc_gcode_command_attr_t){P_existed, P_value}},
            {'E', (lc_gcode_command_attr_t){E_existed, E_value}},
            {'L', (lc_gcode_command_attr_t){L_existed, L_value}}};

        return parsed_gcode_tag_map;
    }

    static void CommandHandlerCallback(const lc_gcode_obj_t *parsed_gcode)
    {
        LC_LOG_INFO("Gcode command %c parsed with Command %d%s",
                    lc_gcode_get_command_type(parsed_gcode),
                    lc_gcode_get_command_number(parsed_gcode),
                    lc_gcode_get_sub_command_existed(parsed_gcode) ? (" and subcommand " + std::to_string(lc_gcode_get_sub_command_number(parsed_gcode))).c_str() : "");

        std::vector<std::pair<const char, lc_gcode_command_attr_t>> parsed_code_attr_map;

        switch (lc_gcode_get_command_type(parsed_gcode))
        {
        case LC_GCODE_TYPE_G:
        {
            parsed_code_attr_map = g_command_attr_map_create(parsed_gcode);
            break;
        }
        case LC_GCODE_TYPE_M:
        {
            parsed_code_attr_map = m_command_attr_map_create(parsed_gcode);
            break;
        }

        default:
            break;
        }

        for (auto pair :parsed_code_attr_map)
        {
            if (pair.second.existed)
                LC_LOG_INFO("%c=%f", pair.first, pair.second.value);
        }
    }
};

TEST_F(LCGcode, initial_t)
{
    lc_gcode_set_handler_callback(CommandHandlerCallback);

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

#ifdef LC_GCODE_PARAMETER_SUPPORT
TEST_F(LCGcode, set_param_named)
{
    #define NAMED_PARAM_ID "named_param_1"
    float named_param_1_value = 1.1234f;
    float named_param_1 = 0;
    lc_gcode_parameter_named_set(NAMED_PARAM_ID, named_param_1_value);

    EXPECT_EQ(lc_gcode_parameter_named_get("named_param_2", &named_param_1), false);
    EXPECT_EQ(lc_gcode_parameter_named_get(NAMED_PARAM_ID, &named_param_1), true);

    EXPECT_EQ(named_param_1, named_param_1_value);
}

TEST_F(LCGcode, set_param_numbered)
{
    #define NUMBERED_PARAM_ID 321
    float numbered_param_1_value = 1.1234f;
    float numbered_param_1 = 0;
    EXPECT_NE(lc_gcode_parameter_numeric_set(1, numbered_param_1_value), LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS); // not in desired user config range
    EXPECT_EQ(lc_gcode_parameter_numeric_set(NUMBERED_PARAM_ID, numbered_param_1_value), LC_GCODE_PARAMETERS_RES_TYPE_SUCCESS); // 

    EXPECT_EQ(lc_gcode_parameter_numeric_get(123, &numbered_param_1), false);
    EXPECT_EQ(lc_gcode_parameter_numeric_get(NUMBERED_PARAM_ID, &numbered_param_1), true);

    EXPECT_EQ(numbered_param_1, numbered_param_1_value);
}
#endif