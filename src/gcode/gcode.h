#ifndef GCODE_H
#define GCODE_H

#include "common_defs.h"

#define LC_GCODE_MAX_LINE_LENTGH 256

typedef enum lc_gcode_command_type_st
{
    LC_GCODE_TYPE_NONE,
    LC_GCODE_TYPE_G,
    LC_GCODE_TYPE_M,
    LC_GCODE_TYPE_F,

    LC_GCODE_TYPE_LAST,
} lc_gcode_command_type_t;

typedef struct lc_gcode_attr_st
{
    bool existed;
    float value;
} lc_gcode_attr_t;

typedef struct lc_gcode_attrbute_value_st
{
    lc_gcode_attr_t X;
    lc_gcode_attr_t Y;
    lc_gcode_attr_t Z;
    lc_gcode_attr_t I;
    lc_gcode_attr_t J;
    lc_gcode_attr_t K;
    lc_gcode_attr_t L;
    lc_gcode_attr_t N;
    lc_gcode_attr_t P;
    lc_gcode_attr_t R;
    lc_gcode_attr_t S;
    lc_gcode_attr_t T;
} lc_gcode_attrbute_value_t;

typedef struct lc_gcode_obj_st
{
    lc_gcode_command_type_t command_type;
    uint32_t command_number;
    bool subcommand_existed;
    uint16_t sub_command_number;
    lc_gcode_attrbute_value_t command_values;
}lc_gcode_obj_t;

typedef void (*lc_gcode_parse_cb_t)(const lc_gcode_obj_t *gcode_obj);

void lc_gcode_init();
void lc_gcode_deinit();
bool lc_gcode_get_initialized();

void lc_gcode_set_parse_cb(lc_gcode_parse_cb_t parse_callback);
bool lc_gcode_feed_line(char *line, size_t *line_number);
bool lc_gcode_set_end_of_file();

bool lc_gcode_process_line(const char *line, size_t line_num);
#endif