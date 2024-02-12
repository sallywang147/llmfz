 #include <fmt/core.h>

#include <cstdint>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size <= 1) return 0;

  const auto format_str = fmt::string_view(as_chars(data), size - 1);
  const auto c = data[size - 1];
  auto f = stderr;
  fmt::detail::print(f, const_cast<char*>(format_str.data()), format_str.size());
  fputc(c, f);
  return 0;
}