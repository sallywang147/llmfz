#include <fuzzer/FuzzedDataProvider.h>

#include <chrono>
#include <iostream>
#include <string>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::chrono::duration<long long, std::ratio<1l, 1000000l> > offset;
  offset.count() = fuzzed_data.ConsumeIntegral<int32_t>();
  cctz::time_zone::Impl *tz = cctz::fixed_time_zone(&offset);
  std::string name = fuzzed_data.ConsumeRandomLengthString();
  tz->set_name(name);
  std::string abbreviation = fuzzed_data.ConsumeRandomLengthString();
  tz->set_abbreviation(abbreviation);
  std::chrono::system_clock::time_point tp;
  cctz::convert(cctz::civil_second(fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>(), fuzzed_data.ConsumeIntegral<uint32_t>()), *tz, &tp);
  cctz::format("%Y-%m-%d %H:%M:%S %z", tp, *tz);

  return 0;
}