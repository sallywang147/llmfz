#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  std::string str1 = fuzzed_data.ConsumeRandomLengthString();
  std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();
  std::string str_result = absl::StrCat(str1, str2);
  std::vector<std::string> v = absl::StrSplit(str_result, ".");
  absl::StrJoin(v, ".");

  bool ret = absl::str_format_internal::FormatArgImpl::Dispatch<char>(
      str_result.data(), str_result.size(), str_result.size(), nullptr);
  return 0;
}