#pragma once

#include <stdint.h>
typedef struct {
  volatile uint32_t lock;
} mutex_t;

void mutex_init(mutex_t *mutex);
void mutex_lock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);
