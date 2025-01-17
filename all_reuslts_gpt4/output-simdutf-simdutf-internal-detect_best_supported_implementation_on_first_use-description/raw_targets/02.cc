#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an instance of unsupported_implementation
  simdutf::internal::unsupported_implementation unsupported_impl;

  // Create an instance of detect_best_supported_implementation_on_first_use
  simdutf::internal::detect_best_supported_implementation_on_first_use best_supported_impl;

  // Call the target function
  std::string* description = best_supported_impl.description(&unsupported_impl);

  // Do something with the result to ensure it's used.
  if (description) {
    delete description;
  }

  return 0;
}