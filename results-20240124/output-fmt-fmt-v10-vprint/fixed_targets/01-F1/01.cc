#include <fmt/core.h>

#include <cstdint>
#include <cstdio>

#include "fuzzer-common.h"

extern "C" {
#include <fmt/format.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static_assert(sizeof(fmt::detail::value<void*>) == 8,
                "fixed size is too small");
  if (size <= fixed_size + 1) return 0;

  const auto args = assign_from_buf<size_t>(data);
  data += fixed_size;
  size -= fixed_size;

  const auto format_str = fmt::string_view(as_chars(data), size);

  fmt::vprint(stdout, format_str, args.data(), args.size());
  return 0;
}