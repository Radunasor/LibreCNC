#ifndef LOGGER_H
#define LOGGER_H

#include "platform_defs.h"

typedef enum
{
    LC_LOGGER_LOG_LEVEL_NONE,
    LC_LOGGER_LOG_LEVEL_TRACE,
    LC_LOGGER_LOG_LEVEL_DEBUG,
    LC_LOGGER_LOG_LEVEL_INFO,
    LC_LOGGER_LOG_LEVEL_WARN,
    LC_LOGGER_LOG_LEVEL_ERROR,
} lc_logger_log_level_t;

#if LC_CONF_LOG_LEVEL > LC_LOGGER_LOG_LEVEL_NONE
#define LC_LOG_TRACE(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_TRACE, __VA_ARGS__);
#else
#define LC_LOG_TRACE(...)
#endif

#if LC_CONF_LOG_LEVEL > LC_LOGGER_LOG_LEVEL_TRACE
#define LC_LOG_DEBUG(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_DEBUG, __VA_ARGS__);
#else
#define LC_LOG_DEBUG(...)
#endif

#if LC_CONF_LOG_LEVEL > LC_LOGGER_LOG_LEVEL_DEBUG
#define LC_LOG_INFO(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_INFO, __VA_ARGS__);
#else
#define LC_LOG_INFO(...)
#endif

#if LC_CONF_LOG_LEVEL > LC_LOGGER_LOG_LEVEL_INFO
#define LC_LOG_WARN(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_WARN, __VA_ARGS__);
#else
#define LC_LOG_WARN(...)
#endif

#if LC_CONF_LOG_LEVEL < LC_LOGGER_LOG_LEVEL_WARN
#define LC_LOG_ERROR(...) lc_logger_log(LC_LOGGER_LOG_LEVEL_ERROR, __VA_ARGS__);
#else
#define LC_LOG_ERROR(...)
#endif

typedef void (*logger_sink_cb_t)(lc_logger_log_level_t level, const char *msg);

void lc_logger_init();
void lc_logger_deinit();

void lc_logger_log(const lc_logger_log_level_t level, const char *format, ...);

void lc_logger_add_sink_cb(logger_sink_cb_t sink_cb);

#endif