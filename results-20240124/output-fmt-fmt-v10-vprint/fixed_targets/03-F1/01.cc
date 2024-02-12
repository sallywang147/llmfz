#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size <= 1) return 0;
  const auto args = data[0];
  data += 1;
  size -= 1;

  const auto format_str = fmt::string_view(as_chars(data), size);

  fmt::detail::value v[args];
  for (size_t i = 0; i < args; ++i) {
    v[i].int_value = i;
  }

  fmt::v10::vprint(stdout, const_cast<char*>(format_str.data()), args, v);
  return 0;
}