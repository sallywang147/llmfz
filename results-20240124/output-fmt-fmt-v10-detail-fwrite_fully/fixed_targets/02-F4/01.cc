#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "fuzzer-common.h"

extern "C" {
#include <fmt/core.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) return 0;

  const size_t count = assign_from_buf<size_t>(data);
  data += sizeof(size_t);
  size -= sizeof(size_t);

  if (size < count) return 0;

  // We use a fixed location for the buffer.
  static_assert(sizeof(char) <= fixed_size, "fixed size is too small");
  char buffer[fixed_size];
  memcpy(buffer, data, count);
  data += count;
  size -= count;

  // We use a fixed location for the FILE.
  static_assert(sizeof(FILE) <= fixed_size, "fixed size is too small");
  FILE* file = reinterpret_cast<FILE*>(buffer);
  if (file == nullptr) return 0;

  // Call the function `fmt::v10::detail::fwrite_fully` to fix the issue.
  fmt::v10::detail::fwrite_fully(buffer, count, file);
  return 0;
}