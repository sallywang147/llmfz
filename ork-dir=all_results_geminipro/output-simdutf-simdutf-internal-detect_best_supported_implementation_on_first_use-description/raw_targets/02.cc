#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"
#include "simdutf/internal/unsupported_implementation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  simdutf::internal::detect_best_supported_implementation_on_first_use instance;
  simdutf::internal::unsupported_implementation unsupported;
  std::string *result = instance.description(&unsupported);
  free(result);
  return 0;
}