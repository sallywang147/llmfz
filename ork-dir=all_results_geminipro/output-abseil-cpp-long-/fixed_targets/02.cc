#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  int64_t long_value = fuzzed_data.ConsumeIntegral<int64_t>();
  std::string str1 = fuzzed_data.ConsumeRandomLengthString();
  std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();

  std::string long_str = absl::StrFormat("%lld", long_value);

  if (!absl::str_format_internal::FormatArgImpl::Dispatch<int64_t>(
          long_str.data(), long_str.size(), 0, nullptr))
    return 0;  // Dispatch the format argument

  absl::StrAppend(&str1, str2);
  std::string str_result = absl::StrCat(str1, long_value);
  std::vector<std::string> v = absl::StrSplit(str_result, ".");
  std::string joined_str = absl::StrJoin(v, ".");  // Store the result in a variable
  return 0;
}