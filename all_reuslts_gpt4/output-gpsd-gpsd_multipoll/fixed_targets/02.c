#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gps.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  bool arg1 = stream.ConsumeBool();
  struct gps_device_t device;
  size_t consumed = stream.ConsumeData(&device, sizeof(device));
  if (consumed != sizeof(device)) return 0;
  float arg4 = stream.ConsumeFloatingPoint<float>();

  // Define a dummy function for the func_type parameter
  void dummy_func() {}

  gpsd_multipoll(arg1, &device, dummy_func, arg4);

  return 0;
}