#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"

extern "C" {
#include "simdutf/public.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  simdutf::internal::detect_best_supported_implementation();
  simdutf::internal::unsupported_implementation impl;
  (void)impl.name(&impl);
  return 0;
}