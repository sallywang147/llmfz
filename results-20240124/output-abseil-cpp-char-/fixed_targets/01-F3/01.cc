#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  float float_value = fuzzed_data.ConsumeFloatingPoint<float>();
  double double_value = fuzzed_data.ConsumeFloatingPoint<double>();
  int int_value = fuzzed_data.ConsumeIntegral<int>();
  bool bool_value = fuzzed_data.ConsumeBool();
  std::string str1 = fuzzed_data.ConsumeRandomLengthString();
  std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();

  std::string float_str = absl::StrFormat("%g", float_value);
  std::string double_str = absl::StrFormat("%g", double_value);
  std::string int_str = absl::StrFormat("%d", int_value);
  std::string bool_str = absl::StrFormat("%d", bool_value);

  // Call the function that was not called by the fuzz target
  absl::str_format_internal::FormatArgImpl::Dispatch<signed char>(
      str1.data(), str1.size(), &int_value, nullptr);

  absl::str_format_internal::FormatArgImpl::Dispatch<signed char>(
      str1.data(), str1.size(), &int_value, nullptr);

  return 0;
}