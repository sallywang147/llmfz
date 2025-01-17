#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  cctz::time_zone::Impl *tz = cctz::local_time_zone();
  if (tz) {
    std::string tz_name = tz->name();
    std::string tz_version = tz->version();
    cctz::time_point<cctz::seconds> tp = tz->utc_to_local(cctz::time_point<cctz::seconds>(cctz::civil_second(fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>())));
  }

  return 0;
}