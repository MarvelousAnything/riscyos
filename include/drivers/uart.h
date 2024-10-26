#pragma once

#include <stdint.h>
struct uart_driver_data {
    uintptr_t base_address;
};

int uart_driver_init();
