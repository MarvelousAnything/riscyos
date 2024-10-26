#include "lib/printf.h"
#include "timer.h"
#include <stdint.h>

void trap_handler() {
  uint64_t cause;

  asm volatile("csrr %0, mcause" : "=r"(cause));

  if ((cause & 0x8000000000000000UL) != 0) {
    uint64_t irq = cause & 0xff;
    switch (irq) {
    case 7:
      timer_handler();
      break;
    default:
      printf("Unhandled interrupt %d\n", irq);
      break;
    }
  } else {
    uint64_t exception_code = cause & 0xff;
    switch (exception_code) {
    default:
      printf("Unhandled exception %d\n", exception_code);
      break;
    }
  }
}
