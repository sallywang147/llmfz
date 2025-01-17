#include <fuzzer/FuzzedDataProvider.h>
#include <absl/strings/str_format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for arguments
  std::string arg = stream.ConsumeRandomLengthString();
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();
  std::string str = stream.ConsumeRandomLengthString();

  // Call the target function
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(arg.data(), spec, out, str.data());

  return 0;
}