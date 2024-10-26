#pragma once

#include <stddef.h>
#include <stdint.h>

struct device;

struct device_operations {
  int (*init)(struct device *dev);
  int (*read)(struct device *dev, void *buffer, size_t size);
  int (*write)(struct device *dev, const void *buffer, size_t size);
  int (*ioctl)(struct device *dev, int command, void *arg);
  int (*shutdown)(struct device *dev);
};

enum device_class {
  DEV_CLASS_GENERIC_IO,
  DEV_CLASS_VIDEO,
  DEV_CLASS_STORAGE,
  DEV_CLASS_NETWORK,
};

struct device {
  const char *name;
  int device_id;
  enum device_class dev_class;
  struct device_operations *ops;
  void *driver_data;
};
