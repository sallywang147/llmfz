#include <fuzzer/FuzzedDataProvider.h>
#include <absl/strings/internal/str_format/arg.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for the arguments
  std::string arg = stream.ConsumeRandomLengthString();
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();
  std::string out_str = stream.ConsumeRandomLengthString();

  // Call the function with the fuzzed arguments
  absl::str_format_internal::FormatArgImpl::Dispatch<long>(arg.data(), spec, out, out_str.data());

  return 0;
}