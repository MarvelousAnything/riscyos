#pragma once

#define MAX_LOG_MESSAGE_LENGTH 256

enum log_level {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL,
};

void log_debug(const char *format, ...);
void log_info(const char *format, ...);
void log_warn(const char *format, ...);
void log_error(const char *format, ...);
void log_fatal(const char *format, ...);

typedef struct log_sink {
  const char *name;
  void (*write)(enum log_level level, const char *message);
  struct log_sink *next;
} log_sink_t;
