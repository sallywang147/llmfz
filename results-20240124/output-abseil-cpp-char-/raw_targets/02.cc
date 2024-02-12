 #include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char arg[1000];
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();
  absl::str_format_internal::FormatArgImpl::Dispatch<signed char>(arg, spec, out, nullptr);
  return 0;
}