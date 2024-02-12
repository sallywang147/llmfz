#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  cctz::seconds offset;
  offset.count() = fuzzed_data.ConsumeIntegral<long long>();
  cctz::time_zone::Impl *tz = cctz::fixed_time_zone(offset);

  return 0;
}