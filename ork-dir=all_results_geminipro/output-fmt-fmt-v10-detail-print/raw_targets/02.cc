#include <cstdio>
#include <cstring>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= 1)
    return 0;

  char *text = as_chars(data);
  size_t len = size - 1;

  // Make sure the input is null-terminated.
  text[len] = '\0';

  // Use a fixed location for the FILE pointer.
  static FILE *f = fopen(fixed_path, "w");
  if (f == nullptr)
    return 0;
  fmt::detail::print(f, text, len);
  return 0;
}