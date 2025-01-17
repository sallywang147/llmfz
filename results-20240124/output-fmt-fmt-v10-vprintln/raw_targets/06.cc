 #include <cstdint>
#include <cstdio>
#include <cstring>
#include <fmt/core.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 10) return 0;
  auto stream = reinterpret_cast<FILE*>(data);
  auto format_str = reinterpret_cast<const char*>(data + sizeof(stream));
  auto format_str_size = size - sizeof(stream);
  fmt::vprintln(stream, format_str, format_str_size, 0, nullptr);
  return 0;
}