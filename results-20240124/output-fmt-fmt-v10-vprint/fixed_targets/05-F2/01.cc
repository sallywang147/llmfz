#include <fmt/core.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size <= 1) return 0;

  const char* format_str = reinterpret_cast<const char*>(data);
  size_t format_size = size - 1;

  std::string arg_str = std::string(data + size, data + size + 1);
  fmt::vprint(stderr, format_str, arg_str);
  return 0;
}