#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"
#include "simdutf/internal/unsupported_implementation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create an instance of unsupported_implementation
  simdutf::internal::unsupported_implementation instance;

  // Create an instance of detect_best_supported_implementation_on_first_use
  simdutf::internal::detect_best_supported_implementation_on_first_use detector;

  // Call the target function
  std::string* result = detector.name(&instance);

  // Cleanup
  delete result;

  return 0;
}