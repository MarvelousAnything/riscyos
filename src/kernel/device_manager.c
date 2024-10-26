#include <drivers/device.h>
#include <kernel/device_manager.h>
#include <lib/string.h>

#define MAX_DEVICES 256
struct device *device_table[MAX_DEVICES];

int register_device(struct device *dev) {
  for (int i = 0; i < MAX_DEVICES; i++) {
    if (device_table[i] == NULL) {
      dev->device_id = i;
      device_table[i] = dev;
      return i;
    }
  }
  return -1;
}

int unregister_device(int device_id) {
  if (device_id < 0 || device_id >= MAX_DEVICES)
    return -1;

  device_table[device_id] = NULL;
  return 0;
}

struct device *get_device_by_id(int device_id) {
  if (device_id < 0 || device_id >= MAX_DEVICES)
    return NULL;
  return device_table[device_id];
}

struct device *get_device_by_name(const char *name) {
  for (int i = 0; i < MAX_DEVICES; i++) {
    if (device_table[i] && strcmp(device_table[i]->name, name) == 0)
      return device_table[i];
  }
  return NULL;
}
