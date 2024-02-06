#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string buf = stream.ConsumeRemainingBytesAsString();

  simdutf::internal::unsupported_implementation impl;
  simdutf::internal::detect_best_supported_implementation_on_first_use detector;

  detector.count_utf8(&impl, buf.data(), buf.size());

  return 0;
}