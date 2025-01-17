 #include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fuzzer-common.h"
#include "fmt/format.h"
#include "fmt/printf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    fmt::printf("Initializing...\n");
    fmt::print("Initializing...\n");
    initialized = true;
  }

  if (size <= 1) return 0;

  const auto format_str = as_chars(data);
  const size_t format_str_len = size - 1;
  data += format_str_len;
  size -= format_str_len;

  // We want to fuzz the format string, so we don't want to use
  // fmt::printf here.
  std::vector<char> buf(format_str_len + 1);
  std::memcpy(buf.data(), format_str, format_str_len);
  buf[format_str_len] = '\0';
  std::fprintf(stderr, "%s", buf.data());

  // We don't want to pass a random number of arguments to vprint.
  const size_t num_args = size / sizeof(fmt::detail::value);
  if (num_args > 100) return 0;

  std::vector<fmt::detail::value> args(num_args);
  for (size_t i = 0; i < num_args; ++i) {
    args[i] = assign_from_buf<fmt::detail::value>(data);
    data += sizeof(fmt::detail::value);
    size -= sizeof(fmt::detail::value);
  }

  fmt::v10::vprint(stderr, buf.data(), num_args, 0, args.data());
  return 0;
}