#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Always use a fixed location of the data.
  static_assert(sizeof(size_t) <= fixed_size, "fixed size is too small");
  if (size <= fixed_size + 1)
    return 0;

  const size_t args = assign_from_buf<size_t>(data);
  data += fixed_size;
  size -= fixed_size;

  // data is already allocated separately in libFuzzer so reading past the end
  // will most likely be detected anyway.
  const auto format_str = fmt::string_view(as_chars(data), size);

  std::ostringstream os;
  fmt::v10::vprint(stdout, const_cast<char *>(format_str.data()), args, 0, nullptr);
  return 0;
}