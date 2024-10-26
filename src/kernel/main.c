#include "putchar.h"
#include "timer.h"
#include <config.h>
#include <drivers/device.h>
#include <drivers/uart.h>
#include <kernel/device_manager.h>
#include <lib/printf.h>
#include <lib/string.h>
#include <stdint.h>

void main() {
#ifdef ENABLE_UART_DRIVER
  uart_driver_init();
#endif
  timer_init();

  struct device *uart_dev = get_device_by_name("uart0");
  if (uart_dev && uart_dev->ops->init) {
    uart_dev->ops->init(uart_dev);
  }

  set_putchar_dev(uart_dev);

  int a = 1;
  int b = 0;
  int c = a/b;

  printf("RiscyOS %s is starting... %d\n", KERNEL_VERSION, c);

  while (1) {
  }
}
