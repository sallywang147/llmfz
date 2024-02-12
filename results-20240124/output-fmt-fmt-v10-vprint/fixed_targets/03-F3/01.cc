#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "fuzzer-common.h"
#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size <= 1) return 0;
  const auto args = data[0];
  data += 1;
  size -= 1;

  const auto format_str = fmt::string_view(as_chars(data), size);

  fmt::detail::value<fmt::format_context> v[args];
  for (size_t i = 0; i < args; ++i) {
    v[i].int_value = i;
  }

  fmt::v10::vprint(stdout, format_str, args, v);
  return 0;
}