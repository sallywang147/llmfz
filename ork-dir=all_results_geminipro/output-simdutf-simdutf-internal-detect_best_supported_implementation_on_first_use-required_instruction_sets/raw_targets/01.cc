#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  simdutf::internal::detect_best_supported_implementation_on_first_use::required_instruction_sets(
      reinterpret_cast<simdutf::internal::unsupported_implementation*>(
          &stream.ConsumeIntegral<uintptr_t>()));
  return 0;
}