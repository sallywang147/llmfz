#include <cstdio>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

extern "C" {
#include "absl/strings/internal/str_format_internal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  std::string str = fuzzed_data.ConsumeRemainingBytesAsString();
  std::vector<std::string> v = absl::StrSplit(str, ".");
  absl::StrJoin(v, ".");
  int spec = fuzzed_data.ConsumeIntegral<int>();
  short arg = fuzzed_data.ConsumeIntegral<short>();
  char out[100];
  absl::str_format_internal::FormatArgImpl::Dispatch<short>(
      reinterpret_cast<char *>(&arg), spec, 100, out);
  return 0;
}