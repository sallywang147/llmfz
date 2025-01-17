#include <fuzzer/FuzzedDataProvider.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "simdutf/internal/detect_best_supported_implementation_on_first_use.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char* input = stream.ConsumeRemainingBytesAsString().c_str();
  size_t length = strlen(input);

  simdutf::internal::detect_best_supported_implementation_on_first_use detector;
  detector.detect_encodings(nullptr, input, length);

  return 0;
}