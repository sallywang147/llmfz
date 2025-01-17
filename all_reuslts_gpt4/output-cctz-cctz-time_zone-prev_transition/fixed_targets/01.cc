#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <chrono>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  cctz::time_zone tz;
  if (!cctz::load_time_zone("UTC", &tz)) {
    return 0;
  }

  // Generate a random time_point
  auto tp = std::chrono::system_clock::from_time_t(stream.ConsumeIntegral<int64_t>());

  cctz::time_zone::civil_transition trans;

  tz.prev_transition(&tp, &trans);

  return 0;
}