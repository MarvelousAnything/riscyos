#include <kernel/mutex.h>
#include <stdint.h>

void mutex_init(mutex_t *mutex) { mutex->lock = 0; }

void mutex_lock(mutex_t *mutex) {
  while (1) {
    uint32_t result;
    __asm__ __volatile__("amoswap.w.aq %0, %2, %1"
                         : "=r"(result), "+A"(mutex->lock)
                         : "r"(1)
                         : "memory");

    if (result == 0) {
      break;
    }
  }

}

void mutex_unlock(mutex_t *mutex) {
  __asm__ __volatile__("amoswap.w.rl x0, x0, %0"
                       : "+A"(mutex->lock)
                       :
                       : "memory");
}
