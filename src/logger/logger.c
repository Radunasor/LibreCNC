#include <stdarg.h>

#include "logger.h"
#include "data_structures/list/list.h"

static void logger_default_sink(lc_logger_log_level_t level, const char *msg);
static logger_sink_cb_t _sink_cb = logger_default_sink;

void lc_logger_log(const lc_logger_log_level_t level, const char *format, ...)
{

    char formatted_text[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(formatted_text, sizeof(formatted_text), format, args);
    va_end(args);

    if (_sink_cb)
        _sink_cb(level, formatted_text);
}

void lc_logger_set_sink_cb(logger_sink_cb_t sink_cb)
{
    _sink_cb = sink_cb;
}

static void logger_default_sink(lc_logger_log_level_t level, const char *msg)
{
    const char *level_str = NULL;

    switch (level)
    {
    case LC_LOGGER_LOG_LEVEL_TRACE:
        level_str = "TRACE";
        break;
    case LC_LOGGER_LOG_LEVEL_DEBUG:
        level_str = "DEBUG";
        break;
    case LC_LOGGER_LOG_LEVEL_INFO:
        level_str = "INFO";
        break;
    case LC_LOGGER_LOG_LEVEL_WARN:
        level_str = "WARN";
        break;
    case LC_LOGGER_LOG_LEVEL_ERROR:
        level_str = "ERROR";
        break;
    default:
        level_str = "UNDEFINED!";
        break;
    }

    printf("[LOG %s]:\"%s\" \n", level_str, msg);
}
