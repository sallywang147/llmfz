#include <fuzzer/FuzzedDataProvider.h>
#include <absl/strings/str_format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char arg = stream.ConsumeIntegral<char>();
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();
  std::string str = stream.ConsumeRandomLengthString();
  char* ptr = const_cast<char*>(str.c_str());

  absl::str_format_internal::FormatArgImpl::Dispatch<char>(&arg, spec, out, ptr);

  return 0;
}