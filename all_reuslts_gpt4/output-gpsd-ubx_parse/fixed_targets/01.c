#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gpsd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct gps_device_t device;
  memset(&device, 0, sizeof(device));

  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();

  ubx_parse(&device, str.data(), str.size());

  return 0;
}