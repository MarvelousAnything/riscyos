#include "drivers/device.h"
#include <kernel/putchar.h>
#include <lib/printf.h>

static struct device *current_dev = NULL;

void set_putchar_dev(struct device *dev) { current_dev = dev; }

void _putchar(char character) {
  current_dev->ops->write(current_dev, &character, 1);
}
