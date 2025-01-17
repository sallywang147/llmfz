#include <fmt/core.h>

#include <cstdint>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Always use a fixed location of the data.
  static_assert(sizeof(uint64_t) <= fixed_size, "fixed size is too small");
  if (size <= fixed_size + 1) return 0;

  const uint64_t args = assign_from_buf<uint64_t>(data);
  data += fixed_size;
  size -= fixed_size;

  // data is already allocated separately in libFuzzer so reading past the end
  // will most likely be detected anyway.
  const auto format_str = fmt::string_view(as_chars(data), size);

  fmt::vprintln(stdout, format_str, fmt::arg(args));
  return 0;
}