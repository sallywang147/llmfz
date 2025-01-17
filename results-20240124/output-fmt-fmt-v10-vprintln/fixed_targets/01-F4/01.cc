#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "fuzzer-common.h"
#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size <= fixed_size + 1) return 0;

  const auto format_str = fmt::string_view(as_chars(data), size - fixed_size);
  data += fixed_size;
  size -= fixed_size;

  std::vector<fmt::detail::value<fmt::format_context>> args;
  while (size > 0) {
    args.emplace_back(fmt::detail::max_value<int64_t>());
    data += sizeof(int64_t);
    size -= sizeof(int64_t);
  }
  fmt::vprintln(stderr, format_str, args);
  return 0;
}