#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fmt/core.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 10) return 0;
  FILE* stream = const_cast<FILE*>(reinterpret_cast<const void*>(data));
  const char* format_str = reinterpret_cast<const char*>(data + sizeof(stream));
  size_t format_str_size = size - sizeof(stream);
  fmt::vprintln(stream, format_str, fmt::format_args(format_str_size));
  return 0;
}