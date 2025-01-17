#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gpsd.h"

// Dummy function to pass as func_type*
void dummy_func(struct gps_device_t* device, char* buf, size_t len) {
  // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract values for function parameters
  bool bool_arg = stream.ConsumeBool();
  float float_arg = stream.ConsumeFloatingPoint<float>();

  // Initialize struct gps_device_t
  struct gps_device_t device;
  memset(&device, 0, sizeof(device));

  // Call the function to fuzz
  gpsd_multipoll(bool_arg, &device, &dummy_func, float_arg);

  return 0;
}