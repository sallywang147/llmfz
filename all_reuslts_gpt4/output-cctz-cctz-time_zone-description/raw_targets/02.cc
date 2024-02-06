#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "cctz/time_zone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize time_zone object
  cctz::time_zone tz;
  if (!cctz::load_time_zone("UTC", &tz)) {
    return 0;
  }

  // Initialize another time_zone object for fuzzing
  cctz::time_zone fuzz_tz;
  if (!cctz::load_time_zone(stream.ConsumeRandomLengthString(), &fuzz_tz)) {
    return 0;
  }

  // Initialize a string object for fuzzing
  std::string fuzz_string = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  tz.description(&fuzz_string, &fuzz_tz);

  return 0;
}