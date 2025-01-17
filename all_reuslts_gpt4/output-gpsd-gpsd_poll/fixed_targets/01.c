#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gpsd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct gps_device_t device;
  memset(&device, 0, sizeof(device));

  // Consume data to fill the gps_device_t structure
  size_t consumed = stream.ConsumeData(&device, sizeof(device));

  // Call the function to fuzz
  gpsd_poll(&device);

  return 0;
}