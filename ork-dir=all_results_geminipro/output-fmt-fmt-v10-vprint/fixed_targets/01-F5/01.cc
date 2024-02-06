#include <fmt/core.h>

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1)
    return 0;

  // Always use a fixed location of the data.
  static_assert(sizeof(size_t) <= fixed_size, "fixed size is too small");
  if (size <= fixed_size + 1)
    return 0;

  const size_t args = assign_from_buf<size_t>(data);
  data += fixed_size;
  size -= fixed_size;

  // data is already allocated separately in libFuzzer so reading past the end
  // will most likely be detected anyway.
  const std::string format_str = as_chars(data, size);

  // Use a fixed file pointer.
  static FILE *f = fopen("/dev/null", "w");

  fmt::v10::detail::value values[args];
  for (size_t i = 0; i < args; ++i) {
    values[i].type = fmt::v10::detail::value_type::int64;
    values[i].int64_value = 0;
  }

  fmt::v10::vprint(f, const_cast<char *>(format_str.c_str()), args, 0, values);
  return 0;
}