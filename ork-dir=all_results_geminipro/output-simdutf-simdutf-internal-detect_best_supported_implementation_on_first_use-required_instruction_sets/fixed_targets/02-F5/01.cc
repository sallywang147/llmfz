#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <string>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"

extern "C" {
#include "simdutf/public.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  simdutf::public::detect_best_supported_implementation_on_first_use
      detect_best_supported_implementation_on_first_use;
  simdutf::public::unsupported_implementation unsupported_implementation;

  detect_best_supported_implementation_on_first_use.detect_best_supported_implementation();
  detect_best_supported_implementation_on_first_use
      .required_instruction_sets(&unsupported_implementation);
  return 0;
}