#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize FuzzedDataProvider.
  FuzzedDataProvider provider(data, size);

  // Call the function under test.
  cctz::time_zone::Impl* local_tz = cctz::local_time_zone();

  // The function does not have any input parameters and does not return any
  // meaningful data that can be used for further fuzzing, so we don't need to
  // do anything else here.

  return 0;
}