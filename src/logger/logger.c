#include <stdarg.h>

#include "logger.h"
#include "data_structures/list/list.h"

static lc_list_t *sink_cb_list = NULL;

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

    printf("[LOG %s]:\"%s\"", level_str, msg);
}

void lc_logger_init()
{
    if (sink_cb_list)
        return;

    sink_cb_list = lc_list_create();

#ifdef LC_DEBUG_BUILD
    if (sink_cb_list)
        lc_logger_add_sink_cb(logger_default_sink);
#endif
}

void lc_logger_deinit()
{
    lc_list_destroy(sink_cb_list);
    sink_cb_list = NULL;
}

void lc_logger_log(const lc_logger_log_level_t level, const char *format, ...)
{

    char formatted_text[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(formatted_text, sizeof(formatted_text), format, args);
    va_end(args);

    logger_sink_cb_t sink_cb = NULL;

    LIST_FOREACH(sink_cb_list, sink_cb)
    sink_cb(level, formatted_text);
}

void lc_logger_add_sink_cb(logger_sink_cb_t sink_cb)
{
    lc_list_insert_back(sink_cb_list, sink_cb);
}
