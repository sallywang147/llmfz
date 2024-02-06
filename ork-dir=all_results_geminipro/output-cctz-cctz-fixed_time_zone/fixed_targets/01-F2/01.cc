#include <fuzzer/FuzzedDataProvider.h>

#include <chrono>
#include <iostream>
#include <string>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::chrono::duration<long long, std::chrono::seconds> offset;
  offset.count() = fuzzed_data.ConsumeIntegral<int32_t>();

  cctz::time_zone::Impl *tz = cctz::fixed_time_zone(&offset);
  std::string str = fuzzed_data.ConsumeRandomLengthString();
  cctz::time_zone lax;
  if (cctz::load_time_zone(str, &lax)) {
    std::chrono::system_clock::time_point tp;
    cctz::convert(cctz::civil_second(fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>()), lax, &tp);
    cctz::convert(tp, tz, &tp);
  }

  return 0;
}