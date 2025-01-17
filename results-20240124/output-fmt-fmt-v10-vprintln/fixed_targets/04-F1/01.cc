#include <fmt/core.h>

#include <cstdint>

#include "fuzzer-common.h"

template <typename T>
void invoke(fmt::string_view format_str, T value) {
  try {
    fmt::print(stderr, format_str.data(), value);
  } catch (std::exception&) {
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Always use a fixed location of the data.
  static_assert(sizeof(uint64_t) <= fixed_size, "fixed size is too small");
  if (size <= fixed_size) return 0;

  const uint64_t value = assign_from_buf<uint64_t>(data);
  data += fixed_size;
  size -= fixed_size;

  // data is already allocated separately in libFuzzer so reading past the end
  // will most likely be detected anyway.
  const auto format_str = fmt::string_view(as_chars(data), size);

  switch (value % 13) {
  case 0:
    invoke<bool>(format_str, value);
    break;
  case 1:
    invoke<char>(format_str, value);
    break;
  case 2:
    invoke<signed char>(format_str, value);
    break;
  case 3:
    invoke<unsigned char>(format_str, value);
    break;
  case 4:
    invoke<short>(format_str, value);
    break;
  case 5:
    invoke<unsigned short>(format_str, value);
    break;
  case 6:
    invoke<int>(format_str, value);
    break;
  case 7:
    invoke<unsigned int>(format_str, value);
    break;
  case 8:
    invoke<long>(format_str, value);
    break;
  case 9:
    invoke<unsigned long>(format_str, value);
    break;
  case 10:
    invoke<float>(format_str, value);
    break;
  case 11:
    invoke<double>(format_str, value);
    break;
  case 12:
    invoke<long double>(format_str, value);
    break;
  }
  return 0;
}