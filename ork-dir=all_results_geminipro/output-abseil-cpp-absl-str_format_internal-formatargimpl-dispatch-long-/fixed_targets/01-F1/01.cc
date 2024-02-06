#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"

extern "C" {
#include "absl/strings/str_format_internal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  long long_value = fuzzed_data.ConsumeIntegral<long>();
  std::string spec = fuzzed_data.ConsumeRandomLengthString();
  int out = fuzzed_data.ConsumeIntegralInRange<int>(0, 10000);

  char buf[1024];
  bool result = absl::str_format_internal::FormatArgImpl::Dispatch<long>(
      reinterpret_cast<char *>(&long_value), spec.c_str(), out, buf);
  if (!result) {
    return 0;
  }
  return 0;
}