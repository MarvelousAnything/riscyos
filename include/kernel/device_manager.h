#pragma once

#include <drivers/device.h>

int register_device(struct device *dev);
int unregister_device(int device_id);
struct device *get_device_by_id(int device_id);
struct device *get_device_by_name(const char *name);
