#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::chrono::duration<long long, std::ratio<1l, 1000000l> > offset;
  offset = std::chrono::duration<long long, std::ratio<1l, 1000000l> >(
      fuzzed_data.ConsumeIntegral<int32_t>());

  cctz::time_zone::Impl *tz = cctz::fixed_time_zone(&offset.count());

  std::chrono::system_clock::time_point tp;
  std::string date_format = fuzzed_data.ConsumeRandomLengthString();
  std::string parse_format = fuzzed_data.ConsumeRandomLengthString();
  cctz::parse(*tz, parse_format, date_format, &tp);

  const auto t1 = cctz::convert(cctz::civil_second(
      fuzzed_data.ConsumeIntegral<uint32_t>(),
      fuzzed_data.ConsumeIntegral<uint32_t>(),
      fuzzed_data.ConsumeIntegral<uint32_t>(),
      fuzzed_data.ConsumeIntegral<uint32_t>(),
      fuzzed_data.ConsumeIntegral<uint32_t>(),
      fuzzed_data.ConsumeIntegral<uint32_t>()), *tz);
  std::string format = fuzzed_data.ConsumeRandomLengthString();
  cctz::format(format, t1, *tz);

  return 0;
}