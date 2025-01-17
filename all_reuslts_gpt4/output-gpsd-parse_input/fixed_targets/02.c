#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "gps.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct gps_device_t device;

  // Initialize the gps_device_t struct with some random data.
  size_t consumed = stream.ConsumeData(&device, sizeof(device));

  // If we couldn't consume enough data for the struct, return early.
  if (consumed != sizeof(device)) {
    return 0;
  }

  // Call the function under test.
  parse_input(&device);

  return 0;
}