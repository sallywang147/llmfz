#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize FuzzedDataProvider using the data provided by the fuzzer
  FuzzedDataProvider fuzzed_data(data, size);
  
  // Call the function to be fuzzed
  cctz::time_zone::Impl* local_tz = cctz::local_time_zone();

  // The function doesn't have any parameters and the return value isn't used, so no further action is needed

  return 0;
}