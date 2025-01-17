#include <fmt/core.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const std::string format_str = provider.ConsumeRemainingBytesAsString();
  const char *format = format_str.c_str();
  size_t args = provider.ConsumeIntegral<size_t>();
  size_t next_arg = provider.ConsumeIntegral<size_t>();
  fmt::v10::detail::value<fmt::v10::basic_format_context<char, char>> *values = nullptr;
  fmt::v10::vprintln(stdout, const_cast<char*>(format), args, next_arg, values);
  return 0;
}