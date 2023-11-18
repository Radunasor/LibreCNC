#ifndef LOGGER_H
#define LOGGER_H

#include "platform_defs.h"

#define LC_LOGGER_LOG_LEVEL_TRACE_D 1
#define LC_LOGGER_LOG_LEVEL_DEBUG_D 2
#define LC_LOGGER_LOG_LEVEL_INFO_D 3
#define LC_LOGGER_LOG_LEVEL_WARN_D 4
#define LC_LOGGER_LOG_LEVEL_ERROR_D 5
#define LC_LOGGER_LOG_LEVEL_OFF_D 6

typedef enum
{
    LC_LOGGER_LOG_LEVEL_TRACE = LC_LOGGER_LOG_LEVEL_TRACE_D,
    LC_LOGGER_LOG_LEVEL_DEBUG = LC_LOGGER_LOG_LEVEL_DEBUG_D,
    LC_LOGGER_LOG_LEVEL_INFO = LC_LOGGER_LOG_LEVEL_INFO_D,
    LC_LOGGER_LOG_LEVEL_WARN = LC_LOGGER_LOG_LEVEL_WARN_D,
    LC_LOGGER_LOG_LEVEL_ERROR = LC_LOGGER_LOG_LEVEL_ERROR_D,
    LC_LOGGER_LOG_LEVEL_OFF = LC_LOGGER_LOG_LEVEL_OFF_D,
} lc_logger_log_level_t;

#if LC_CONF_LOG_LEVEL <= LC_LOGGER_LOG_LEVEL_TRACE_D
#define LC_LOG_TRACE(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_TRACE, __VA_ARGS__);
#else
#define LC_LOG_TRACE(...)
#endif

#if LC_CONF_LOG_LEVEL <= LC_LOGGER_LOG_LEVEL_DEBUG_D
#define LC_LOG_DEBUG(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_DEBUG, __VA_ARGS__);
#else
#define LC_LOG_DEBUG(...)
#endif

#if LC_CONF_LOG_LEVEL <= LC_LOGGER_LOG_LEVEL_INFO_D
#define LC_LOG_INFO(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_INFO, __VA_ARGS__);
#else
#define LC_LOG_INFO(...)
#endif

#if LC_CONF_LOG_LEVEL <= LC_LOGGER_LOG_LEVEL_WARN_D
#define LC_LOG_WARN(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_WARN, __VA_ARGS__);
#else
#define LC_LOG_WARN(...)
#endif

#if LC_CONF_LOG_LEVEL <= LC_LOGGER_LOG_LEVEL_ERROR_D
#define LC_LOG_ERROR(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_ERROR, __VA_ARGS__);
#else
#define LC_LOG_ERROR(...)
#endif

typedef void (*logger_sink_cb_t)(lc_logger_log_level_t level, const char *msg);

void lc_logger_init();
void lc_logger_deinit();

void lc_logger_log(const lc_logger_log_level_t level, const char *format, ...);

void lc_logger_set_sink_cb(logger_sink_cb_t sink_cb);

#endif