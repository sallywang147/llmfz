#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an unsupported_implementation object
  simdutf::internal::unsupported_implementation impl;

  // Create a char array from the fuzzed data
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* input = str.c_str();

  // Call the function to fuzz
  simdutf::internal::detect_best_supported_implementation_on_first_use::detect_encodings(&impl, input, size);

  return 0;
}