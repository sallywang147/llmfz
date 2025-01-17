#include <fuzzer/FuzzedDataProvider.h>

#include <string>

#include "cctz/time_zone.h"

extern "C" {
#include "cctz/time_zone.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  cctz::time_zone local_time_zone = cctz::local_time_zone();
  (void)local_time_zone;
  return 0;
}