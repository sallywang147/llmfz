#include <fmt/core.h>

#include <cstdint>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) return 0;

  size_t count = data[0];
  if (count >= size) return 0;

  const char* ptr = reinterpret_cast<const char*>(data + 1);
  FILE* stream = stderr;
  try {
    fmt::detail::fwrite_fully(ptr, count, stream);
  } catch (const std::exception& e) {
    // ignore
  }
  return 0;
}