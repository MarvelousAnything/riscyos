#include "lib/printf.h"
#include <stdint.h>

void syscall_handler() {
  uint64_t syscall_num;
  uint64_t arg0, arg1, arg2;
  uint64_t return_value = 0;

  /* Retrieve syscall number and arguments from registers */
  asm volatile("mv %0, a7" : "=r"(syscall_num)); // Syscall number in a7
  asm volatile("mv %0, a0" : "=r"(arg0));        // arg0 in a0
  asm volatile("mv %0, a1" : "=r"(arg1));        // arg1 in a1
  asm volatile("mv %0, a2" : "=r"(arg2));        // arg2 in a2

  printf("syscall %d: %d, %d, %d\n", syscall_num, arg0, arg1, arg2);

  asm volatile("mv a0, %0" ::"r"(return_value));
}
