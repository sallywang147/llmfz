#include <fmt/core.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static_assert(sizeof(size_t) == sizeof(uint32_t), "size_t is not 32-bit");
  static_assert(sizeof(uint32_t) == 4, "uint32_t is not 4-byte");

  // Always use a fixed location of the data.
  constexpr size_t fixed_size = 1024;
  static_assert(sizeof(uint32_t) <= fixed_size, "fixed size is too small");
  if (size <= fixed_size + 1) return 0;

  const uint32_t args = assign_from_buf<uint32_t>(data);
  data += fixed_size;
  size -= fixed_size;

  // data is already allocated separately in libFuzzer so reading past the end
  // will most likely be detected anyway.
  const auto format_str = fmt::string_view(as_chars(data), size);

  try {
    fmt::vprintln(stderr, format_str, args);
  } catch (std::exception&) {
  }
  return 0;
}
}  // extern "C"