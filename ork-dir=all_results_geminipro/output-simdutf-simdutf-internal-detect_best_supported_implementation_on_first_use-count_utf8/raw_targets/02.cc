#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "simdutf/utf8.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  simdutf::internal::detect_best_supported_implementation_on_first_use::count_utf8(
      nullptr, const_cast<char*>(text.c_str()), text.size());
  return 0;
}