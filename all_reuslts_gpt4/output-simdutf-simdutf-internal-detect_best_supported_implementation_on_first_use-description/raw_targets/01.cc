#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  simdutf::internal::unsupported_implementation unsupported_impl;
  
  simdutf::internal::detect_best_supported_implementation_on_first_use detector;
  std::string* description = detector.description(&unsupported_impl);
  
  delete description;

  return 0;
}