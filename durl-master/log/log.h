#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define logt(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define logd(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define logi(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define logw(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define loge(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define logf(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_set_level(int level);
void log_set_quiet(int enable);

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif
