#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"

extern "C" {
#include "simdutf/public/simdutf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  simdutf::internal::unsupported_implementation unsupported_implementation;
  const std::string* description =
      simdutf::internal::detect_best_supported_implementation_on_first_use::
          description(&unsupported_implementation);
  (void)description;  // Avoid unused variable warning.
  return 0;
}