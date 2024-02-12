#include <cstdint>
#include <cstdio>
#include <string>

#include "fuzzer-common.h"

#include <fmt/format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) return 0;
  const auto text = as_chars(data);
  fmt::print(stdout, "{}", text);
  return 0;
}