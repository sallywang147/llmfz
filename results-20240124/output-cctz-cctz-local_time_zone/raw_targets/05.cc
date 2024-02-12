 #include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  cctz::time_zone::Impl * tz = cctz::local_time_zone();
  if (tz == nullptr) {
    return 0;
  }

  std::string format = fuzzed_data.ConsumeRandomLengthString();
  cctz::format(format, std::chrono::system_clock::now(), *tz);
  return 0;
}