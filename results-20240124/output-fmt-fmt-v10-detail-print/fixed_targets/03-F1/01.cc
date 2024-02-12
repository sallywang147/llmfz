#include <cstdint>
#include <cstdio>

#include "fuzzer-common.h"
#include "fmt/format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size <= 0) return 0;

  const auto text = as_chars(data);
  const auto size_t_max = static_cast<size_t>(-1);
  fmt::print(stdout, const_cast<char*>(text), size_t_max);
  return 0;
}