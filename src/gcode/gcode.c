#include <string.h>

#include "gcode.h"
#include "parser.h"

#define CHECK_INITIALIIZED LC_ASSERT(initialized, "GCODE module not initialized!");

static bool initialized = false;

static lc_gcode_obj_t gcode_obj = {
    .command_number = 0,
    .command_type = LC_GCODE_TYPE_NONE,
    .command_values = NULL,
    .subcommand_existed = false,
    .sub_command_number = 0,
};

static lc_interface_gcode_t gcode_user_callbacks = {
    .lc_interface_gcode_deinit = NULL,
    .lc_interface_gcode_init = NULL,
    .lc_interface_gcode_get_line = NULL,
};

static lc_gcode_cb_t gcode_parser_callback = NULL;

static lc_gcode_attrbute_value_t line_gcode_attributes =
    {
        .X = {false, 0},
        .Y = {false, 0},
        .Z = {false, 0},
        .I = {false, 0},
        .J = {false, 0},
        .K = {false, 0},
        .L = {false, 0},
        .N = {false, 0},
        .P = {false, 0},
        .R = {false, 0},
        .S = {false, 0},
        .T = {false, 0},
};

/******************************************************/
/***********static functions declarations**************/
/******************************************************/
static void lc_gcode_parse_line(char *line);
/******************************************************/

void lc_gcode_init(lc_interface_gcode_t *gcode_cbs)
{
    if (initialized)
        return;

    if (!gcode_cbs)
    {
        LC_LOG_ERROR("gcode module initialized with NULL interface pointer");
        return;
    }

    gcode_user_callbacks = *gcode_cbs;

    initialized = true;
}

void lc_gcode_deinit()
{
    if (!initialized)
        return;

    memset(&line_gcode_attributes, 0, sizeof(lc_gcode_attrbute_value_t));
    memset(&gcode_user_callbacks, 0, sizeof(lc_interface_gcode_t));
    initialized = false;
}

bool lc_gcode_get_initialized()
{
    return initialized;
}

void lc_gcode_set_parse_callback(lc_gcode_cb_t parse_cb)
{
        gcode_parser_callback = parse_cb;
}

bool lc_gcode_process_line()
{
    CHECK_INITIALIIZED

    if (!gcode_parser_callback)
    {
        LC_LOG_ERROR("no callback set for parsed gcodes");
        return false;
    }

    char line[256] = {0};
    size_t line_num = 0;
    
    if(!gcode_user_callbacks.lc_interface_gcode_get_line(line, &line_num))
        return false;

    lc_gcode_parse_line(line);

    return true;
}

/*********************************************************/
/***********static functions implementations**************/
/*********************************************************/
static void lc_gcode_parse_line(char *line)
{
    lc_gcode_parser_mark_comments(line);

    struct lc_gcode_parse_tag_map
    {
        const char tag;
        lc_gcode_attr_t *attr;
    } lc_gcode_parser_tag_map[] = {
        {'X', &line_gcode_attributes.X},
        {'Y', &line_gcode_attributes.Y},
        {'Z', &line_gcode_attributes.Z},
        {'I', &line_gcode_attributes.I},
        {'J', &line_gcode_attributes.J},
        {'K', &line_gcode_attributes.K},
        {'L', &line_gcode_attributes.L},
        {'N', &line_gcode_attributes.N},
        {'P', &line_gcode_attributes.P},
        {'R', &line_gcode_attributes.R},
        {'S', &line_gcode_attributes.S},
        {'T', &line_gcode_attributes.T},

        {'\0', NULL},
    };

    for (uint8_t i = 0; lc_gcode_parser_tag_map[i].tag; i++)
        lc_gcode_parser_tag_map[i].attr->existed = lc_gcode_parser_get_value(line, lc_gcode_parser_tag_map[i].tag, &(lc_gcode_parser_tag_map[i].attr->value));

    lc_gcode_command_type_t lc_gcode_command_type_arr[] = {
        LC_GCODE_TYPE_F,
        LC_GCODE_TYPE_M,
        LC_GCODE_TYPE_G,

        LC_GCODE_TYPE_LAST,
    }; // order is important

    uint32_t command = 0;
    uint16_t sub_command = 0;
    bool subcommand_existed = false;
    const char *command_ptr = line;

    for (uint8_t i = 0; lc_gcode_command_type_arr[i] != LC_GCODE_TYPE_LAST; i++)
    {
        command_ptr = line;

        while (lc_gcode_parser_get_command(&command_ptr, lc_gcode_command_type_arr[i], &command, &subcommand_existed, &sub_command))
        {
            gcode_obj.command_type = lc_gcode_command_type_arr[i];
            gcode_obj.command_number = command;
            gcode_obj.subcommand_existed = subcommand_existed;
            gcode_obj.sub_command_number = sub_command;
            gcode_obj.command_values = line_gcode_attributes;

            gcode_parser_callback(&gcode_obj);
        }
    }
}
/*********************************************************/
