#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "gps.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct gps_device_t device;
  memset(&device, 0, sizeof(device));
  device.context = (struct gps_context_t*)calloc(1, sizeof(struct gps_context_t));
  if (device.context == nullptr) {
    return 0;
  }

  size_t consumed = stream.ConsumeData(&device, sizeof(device));
  if (consumed != sizeof(device)) {
    free(device.context);
    return 0;
  }

  gpsd_poll(&device);

  free(device.context);
  return 0;
}