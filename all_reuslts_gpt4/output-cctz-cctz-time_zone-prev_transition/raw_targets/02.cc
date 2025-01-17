#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize cctz::time_zone
  cctz::time_zone tz;
  if (!cctz::load_time_zone("UTC", &tz)) {
    return 0;
  }

  // Consume data to construct time_point
  auto tp = std::chrono::system_clock::from_time_t(stream.ConsumeIntegral<time_t>());

  cctz::time_zone::civil_transition trans;

  // Call the function under test
  bool result = tz.prev_transition(&tp, &trans);

  return 0;
}