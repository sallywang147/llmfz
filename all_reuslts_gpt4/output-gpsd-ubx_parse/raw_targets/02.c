#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "gps.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct gps_device_t device;
  FuzzedDataProvider provider(data, size);

  size_t data_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::string fuzzed_data = provider.ConsumeBytesAsString(data_size);

  ubx_parse(&device, fuzzed_data.data(), fuzzed_data.size());

  return 0;
}