#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <string>

extern "C" {
#include "cctz/time_zone.h"
#include "cctz/civil_time_detail.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  cctz::time_zone tz = cctz::local_time_zone();
  if (tz.impl_ == nullptr) {
    return 0;
  }

  std::string format = fuzzed_data.ConsumeRandomLengthString();
  cctz::format(format, std::chrono::system_clock::now(), tz);
  return 0;
}