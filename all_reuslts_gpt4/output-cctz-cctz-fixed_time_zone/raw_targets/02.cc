#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <chrono>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  long long int_arg = stream.ConsumeIntegral<long long>();

  // Create a duration object using the extracted integral value
  std::chrono::duration<long long> offset(int_arg);

  // Call the function with the created duration object
  cctz::time_zone::Impl* timeZone = cctz::fixed_time_zone(&offset);

  return 0;
}