#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "gpsd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const bool wait = provider.ConsumeBool();
  const float timeout = provider.ConsumeFloatingPoint<float>();
  gps_device_t* dev = nullptr;
  func_type* callbacks = nullptr;

  gpsd_multipoll(wait, dev, callbacks, timeout);

  return 0;
}