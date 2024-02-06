#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"
#include "simdutf/internal/unsupported_implementation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  simdutf::internal::unsupported_implementation obj;
  std::string *result = obj.name(&obj);
  delete result;
  return 0;
}