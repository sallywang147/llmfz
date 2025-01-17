#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>

#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  simdutf::internal::unsupported_implementation instance;
  simdutf::internal::detect_best_supported_implementation_on_first_use detector;

  int result = detector.required_instruction_sets(&instance);

  return 0;
}