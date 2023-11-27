#ifndef DEFAULT_CONFIGS_H
#define DEFAULT_CONFIGS_H

#include "config.h"

/**
 * @struct lc_config_table_default_t
 * @brief Structure representing a default configuration entry.
 *
 * This structure associates a configuration key with its default float value.
 */
typedef struct
{
    lc_config_key_t key; ///< The configuration key.
    float value;         ///< The default float value associated with the key.
} lc_config_table_default_t;

lc_config_table_default_t default_config_table[] =
    {
        {LC_CONFIG_KEY_X_STEPS_PER_MM, 250.0},
        {LC_CONFIG_KEY_Y_STEPS_PER_MM, 250.0},
        {LC_CONFIG_KEY_Z_STEPS_PER_MM, 250.0},
        {LC_CONFIG_KEY_X_MAX_RATE, 500},
        {LC_CONFIG_KEY_Y_MAX_RATE, 500},
        {LC_CONFIG_KEY_Z_MAX_RATE, 500},
        {LC_CONFIG_KEY_X_ACCELERATION, (10.0 * 60 * 60)},
        {LC_CONFIG_KEY_Y_ACCELERATION, (10.0 * 60 * 60)},
        {LC_CONFIG_KEY_Z_ACCELERATION, (10.0 * 60 * 60)},
        {LC_CONFIG_KEY_X_MAX_TRAVEL, 200},
        {LC_CONFIG_KEY_Y_MAX_TRAVEL, 200},
        {LC_CONFIG_KEY_Z_MAX_TRAVEL, 200},
        {LC_CONFIG_KEY_STEP_PULSE_MICROSECONDS, 10},
        {LC_CONFIG_KEY_STEPPING_INVERT_MASK, 0},
        {LC_CONFIG_KEY_DIRECTION_INVERT_MASK, 0},
        {LC_CONFIG_KEY_STEPPER_IDLE_LOCK_TIME, 25},
        {LC_CONFIG_KEY_JUNCTION_DEVIATION, 0.01},
        {LC_CONFIG_KEY_ARC_TOLERANCE, 0.002},
        {LC_CONFIG_KEY_REPORT_INCHES, 0},
        {LC_CONFIG_KEY_INVERT_ST_ENABLE, 0},
        {LC_CONFIG_KEY_INVERT_LIMIT_PINS, 0},
        {LC_CONFIG_KEY_SOFT_LIMIT_ENABLE, 0},
        {LC_CONFIG_KEY_HARD_LIMIT_ENABLE, 0},
        {LC_CONFIG_KEY_HOMING_ENABLE, 0},
        {LC_CONFIG_KEY_HOMING_DIR_MASK, 0},
        {LC_CONFIG_KEY_HOMING_FEED_RATE, 25.0},
        {LC_CONFIG_KEY_HOMING_SEEK_RATE, 500.0},
        {LC_CONFIG_KEY_HOMING_DEBOUNCE_DELAY, 250.0},
        {LC_CONFIG_KEY_HOMING_PULLOFF, 1.0},

        {_LC_CONFIG_KEY_LAST, 0},
};

#endif