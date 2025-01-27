#ifndef CONFIG_KEYS_H
#define CONFIG_KEYS_H

typedef enum
{
    LC_CONFIG_KEY_X_STEPS_PER_MM,
    LC_CONFIG_KEY_Y_STEPS_PER_MM,
    LC_CONFIG_KEY_Z_STEPS_PER_MM,
    LC_CONFIG_KEY_X_MAX_RATE,
    LC_CONFIG_KEY_Y_MAX_RATE,
    LC_CONFIG_KEY_Z_MAX_RATE,
    LC_CONFIG_KEY_X_ACCELERATION,
    LC_CONFIG_KEY_Y_ACCELERATION,
    LC_CONFIG_KEY_Z_ACCELERATION,
    LC_CONFIG_KEY_X_MAX_TRAVEL,
    LC_CONFIG_KEY_Y_MAX_TRAVEL,
    LC_CONFIG_KEY_Z_MAX_TRAVEL,
    LC_CONFIG_KEY_STEP_PULSE_MICROSECONDS,
    LC_CONFIG_KEY_STEPPING_INVERT_MASK,
    LC_CONFIG_KEY_DIRECTION_INVERT_MASK,
    LC_CONFIG_KEY_STEPPER_IDLE_LOCK_TIME,
    LC_CONFIG_KEY_JUNCTION_DEVIATION,
    LC_CONFIG_KEY_ARC_TOLERANCE,
    LC_CONFIG_KEY_REPORT_INCHES,
    LC_CONFIG_KEY_INVERT_ST_ENABLE,
    LC_CONFIG_KEY_INVERT_LIMIT_PINS,
    LC_CONFIG_KEY_SOFT_LIMIT_ENABLE,
    LC_CONFIG_KEY_HARD_LIMIT_ENABLE,
    LC_CONFIG_KEY_HOMING_ENABLE,
    LC_CONFIG_KEY_HOMING_DIR_MASK,
    LC_CONFIG_KEY_HOMING_FEED_RATE,
    LC_CONFIG_KEY_HOMING_SEEK_RATE,
    LC_CONFIG_KEY_HOMING_DEBOUNCE_DELAY,
    LC_CONFIG_KEY_HOMING_PULLOFF,

    LC_CONFIG_KEY_LAST
} lc_config_default_key_t;

#endif