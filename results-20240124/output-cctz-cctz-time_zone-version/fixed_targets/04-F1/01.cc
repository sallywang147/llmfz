#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::string tz = fuzzed_data.ConsumeRandomLengthString();
  cctz::time_zone lax;
  if (load_time_zone(tz, &lax)) {
    std::string version = lax.version();  // Fix: remove the &
  }

  return 0;
}