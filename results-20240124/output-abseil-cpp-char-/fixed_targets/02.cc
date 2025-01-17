#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include <absl/strings/str_format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char arg[1000];
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();
  bool ret = absl::str_format_internal::FormatArgImpl::Dispatch<signed char>(arg, spec, out, nullptr);
  // Call the function `bool absl::str_format_internal::FormatArgImpl::Dispatch<signed char>(char * arg, size_t spec, int out, char * )`
  // inside function `LLVMFuzzerTestOneInput`.
  return ret;
}