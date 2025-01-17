#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create an instance of unsupported_implementation
  simdutf::internal::unsupported_implementation instance;

  // Call the function required_instruction_sets
  int result = simdutf::internal::detect_best_supported_implementation_on_first_use::required_instruction_sets(&instance);

  return 0;
}