#include "kernel/timer.h"
#include "lib/printf.h"
#include <stdint.h>

#define CLINT_BASE 0x02000000UL
#define CLINT_MTIMECMP (CLINT_BASE + 0x4000)
#define CLINT_MTIME (CLINT_BASE + 0xBFF8)

static uint64_t timer_interval = 1000000;

void timer_init() {
  uint64_t current_time = *(volatile uint64_t *)CLINT_MTIME;
  uint64_t next_time = current_time + timer_interval;
  *(volatile uint64_t *)CLINT_MTIMECMP = next_time;

  uint64_t mie;
  asm volatile("csrr %0, mie" : "=r"(mie));
  mie |= (1 << 7);
  asm volatile("csrw mie, %0" ::"r"(mie));
}

void timer_handler() {
  printf(".");

  uint64_t current_time = *(volatile uint64_t *)CLINT_MTIME;
  uint64_t next_time = current_time + timer_interval;
  *(volatile uint64_t *)CLINT_MTIMECMP = next_time;
}
