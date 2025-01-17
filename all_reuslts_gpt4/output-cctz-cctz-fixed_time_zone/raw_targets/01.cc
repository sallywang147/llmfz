#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <chrono>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int64_t offset_value = stream.ConsumeIntegral<int64_t>();

  // Create a duration from the extracted value
  std::chrono::duration<int64_t> offset(offset_value);

  // Call the target function
  cctz::time_zone::Impl* result = cctz::fixed_time_zone(&offset);

  // We don't actually need to do anything with the result, as we're just testing
  // the function for crashes, not correctness.

  return 0;
}