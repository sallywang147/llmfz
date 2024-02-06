#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an unsupported_implementation object
  simdutf::internal::unsupported_implementation unsupported_impl;

  // Call the name function on detect_best_supported_implementation_on_first_use object
  simdutf::internal::detect_best_supported_implementation_on_first_use detector;
  std::string* name = detector.name(&unsupported_impl);

  // The returned name string is not used, but we need to call the function to fuzz it.
  // So, just delete the returned string to avoid memory leak.
  delete name;

  return 0;
}