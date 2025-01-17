#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) return 0;
  // Always use a fixed location of the data.
  static_assert(sizeof(size_t) <= fixed_size, "fixed size is too small");
  if (size <= fixed_size + 1) return 0;

  const size_t count = assign_from_buf<size_t>(data);
  data += fixed_size;
  size -= fixed_size;

  // data is already allocated separately in libFuzzer so reading past the end
  // will most likely be detected anyway.
  const auto text = fmt::string_view(as_chars(data), size);

  // Write to a temporary file.
  FILE* f = tmpfile();
  if (f == nullptr) return 0;

  fmt::detail::print(f, const_cast<char*>(text.data()), text.size());
  fclose(f);
  return 0;
}