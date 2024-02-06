#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gps.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct gps_device_t device;
  memset(&device, 0, sizeof(device));

  // Consume some random bytes for the device's input buffer
  size_t buf_size = stream.ConsumeIntegralInRange<size_t>(0, sizeof(device.gpsdata));
  std::vector<uint8_t> buf = stream.ConsumeBytes<uint8_t>(buf_size);
  memcpy(device.gpsdata, buf.data(), buf.size());

  // Call the function to fuzz
  parse_input(&device);

  return 0;
}