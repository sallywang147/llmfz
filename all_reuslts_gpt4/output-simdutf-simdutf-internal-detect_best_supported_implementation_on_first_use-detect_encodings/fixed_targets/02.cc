#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for input string
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *input = const_cast<char *>(str.c_str());
  size_t length = str.size();

  // Create an instance of unsupported_implementation
  simdutf::internal::unsupported_implementation implementation;

  // Call the function to fuzz
  simdutf::internal::detect_best_supported_implementation_on_first_use detector;
  detector.detect_encodings(&implementation, input, length);

  return 0;
}