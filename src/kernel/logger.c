#include "kernel/logger.h"
#include "kernel/mutex.h"
#include "lib/printf.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

static log_sink_t *log_sinks = NULL;
static mutex_t logger_mutex;

void logger_init() { mutex_init(&logger_mutex); }

void logger_register_sink(log_sink_t *sink) {
  mutex_lock(&logger_mutex);
  sink->next = log_sinks;
  log_sinks = sink;
  mutex_unlock(&logger_mutex);
}

void logger_unregister_sink(log_sink_t *sink) {
  mutex_lock(&logger_mutex);
  log_sink_t **current = &log_sinks;
  while (*current) {
    if (*current == sink) {
      *current = sink->next;
      break;
    }
    current = &((*current)->next);
  }
  mutex_unlock(&logger_mutex);
}

static void logger_dispatch(enum log_level level, const char *message) {
  mutex_lock(&logger_mutex);
  log_sink_t *sink = log_sinks;
  while (sink) {
    sink->write(level, message);
    sink = sink->next;
  }
  mutex_unlock(&logger_mutex);
}

static void log_message(enum log_level level, const char *format,
                        va_list args) {
  char message[MAX_LOG_MESSAGE_LENGTH];
  int length = vsnprintf(message, sizeof(message), format, args);
  if (length >= (int)sizeof(message)) {
    message[sizeof(message) - 1] = '\0';
  }
  logger_dispatch(level, message);
}

void log_debug(const char *format, ...) {
  va_list args;
  va_start(args, format);
  log_message(LOG_LEVEL_DEBUG, format, args);
  va_end(args);
}

void log_info(const char *format, ...) {
  va_list args;
  va_start(args, format);
  log_message(LOG_LEVEL_INFO, format, args);
  va_end(args);
}

void log_warn(const char *format, ...) {
  va_list args;
  va_start(args, format);
  log_message(LOG_LEVEL_WARN, format, args);
  va_end(args);
}

void log_error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  log_message(LOG_LEVEL_ERROR, format, args);
  va_end(args);
}

void log_fatal(const char *format, ...) {
  va_list args;
  va_start(args, format);
  log_message(LOG_LEVEL_FATAL, format, args);
  va_end(args);
}
