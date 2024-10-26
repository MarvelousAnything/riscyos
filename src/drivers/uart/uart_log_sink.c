#include "drivers/uart.h"
#include "kernel/logger.h"
#include "lib/printf.h"

static const char *log_level_strings[] = {"DEBUG", "INFO", "WARN", "ERROR",
                                          "FATAL"};

static void uart_log_write(enum log_level level, const char *message) {
  char buffer[MAX_LOG_MESSAGE_LENGTH + 16];
  snprintf_(buffer, sizeof(buffer), "[%s] %s\n", log_level_strings[level],
            message);
}
