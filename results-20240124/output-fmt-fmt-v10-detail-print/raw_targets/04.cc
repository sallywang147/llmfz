 #include <cstdint>
#include <cstdio>
#include <string>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) return 0;
  const auto text = as_chars(data);
  fmt::v10::detail::print(stdout, const_cast<char*>(text), size);
  return 0;
}