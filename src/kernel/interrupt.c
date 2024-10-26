#include "interrupt.h"

void enable_interrupts() {
  asm volatile("csrsi mstatus, 0x8");
}

void disable_interrupts() {
  asm volatile("csrci mstatus, 0x8");
}
