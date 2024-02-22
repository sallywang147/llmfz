#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  short short_value = fuzzed_data.ConsumeIntegral<short>();
  std::string str1 = fuzzed_data.ConsumeRandomLengthString();
  std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();

  absl::StrAppend(&str1, str2);
  std::string str_result = absl::StrCat(str1, short_value);
  std::vector<std::string> v = absl::StrSplit(str_result, ".");
  absl::StrJoin(v, ".");

  // Fix the issue by calling the function.
  absl::str_format_internal::FormatArgImpl::Dispatch<short>(nullptr, 0, 0, nullptr);
  return 0;
}