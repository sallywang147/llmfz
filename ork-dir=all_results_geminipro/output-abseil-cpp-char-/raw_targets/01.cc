#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  std::string format_str = fuzzed_data.ConsumeRandomLengthString();
  std::vector<std::string> args;
  while (fuzzed_data.remaining_bytes() > 0) {
    args.push_back(fuzzed_data.ConsumeRandomLengthString());
  }

  std::string result;
  absl::StrAppendFormat(&result, format_str, args);

  char arg = fuzzed_data.ConsumeIntegral<char>();
  size_t spec = fuzzed_data.ConsumeIntegral<size_t>();
  int out = fuzzed_data.ConsumeIntegral<int>();
  char *out_ptr = fuzzed_data.ConsumeBytes<char>(out).data();
  absl::str_format_internal::FormatArgImpl::Dispatch<signed char>(
      &arg, spec, out, out_ptr);

  return 0;
}