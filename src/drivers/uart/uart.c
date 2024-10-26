#include <drivers/uart.h>

#include <drivers/device.h>
#include <kernel/device_manager.h>
#include <stddef.h>
#include <stdint.h>

#define UART0_BASE 0x10000000UL
#define UART_THR (UART0_BASE + 0x00) /* Transmit Holding Register */
#define UART_RBR (UART0_BASE + 0x00) /* Receive Buffer Register */
#define UART_LSR (UART0_BASE + 0x05) /* Line Status Register */
#define UART_LSR_DR 0x01             /* Data Ready */
#define UART_LSR_THRE 0x20           /* Transmitter Holding Register Empty */

static inline void mmio_write(uint64_t reg, uint8_t val) {
  *(volatile uint8_t *)reg = val;
}

static inline uint8_t mmio_read(uint64_t reg) {
  return *(volatile uint8_t *)reg;
}

int uart_init(__attribute__((unused)) struct device *dev) { return 0; }

void uart_putc(char c) {
  while ((mmio_read(UART_LSR) & UART_LSR_THRE) == 0)
    ;
  mmio_write(UART_THR, c);
}

static int uart_read(__attribute__((unused)) struct device *dev, void *buffer,
                     size_t size) {
  char *buf = (char *)buffer;
  size_t bytes_read = 0;

  while (bytes_read < size) {
    while ((mmio_read(UART_LSR) & UART_LSR_DR) == 0)
      ;
    buf[bytes_read++] = mmio_read(UART_RBR);
  }

  return bytes_read;
}

static int uart_write(__attribute__((unused)) struct device *dev,
                      const void *buffer, size_t size) {
  const char *buf = (const char *)buffer;
  size_t bytes_written = 0;

  while (bytes_written < size) {
    if (buf[bytes_written] == '\n') {
      uart_putc('\r');
    }
    uart_putc(buf[bytes_written++]);
  }

  return bytes_written;
}

static int uart_ioctl(__attribute__((unused)) struct device *dev,
                      __attribute__((unused)) int command,
                      __attribute__((unused)) void *arg) {
  return -1;
}

static int uart_shutdown(__attribute__((unused)) struct device *dev) {
  return 0;
}

static struct device_operations uart_ops = {
    .init = uart_init,
    .read = uart_read,
    .write = uart_write,
    .ioctl = uart_ioctl,
    .shutdown = uart_shutdown,
};

int uart_driver_init() {
  static struct uart_driver_data uart_data = {.base_address = UART0_BASE};

  static struct device uart_device = {
      .name = "uart0",
      .dev_class = DEV_CLASS_GENERIC_IO,
      .ops = &uart_ops,
      .driver_data = &uart_data,
  };

  return register_device(&uart_device);
}
