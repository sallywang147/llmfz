#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format_internal.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  short short_value = fuzzed_data.ConsumeIntegral<short>();
  std::string short_str = absl::StrFormat("%hd", short_value);

  // Call the function that was not called by the fuzz target.
  char arg[100];
  absl::str_format_internal::FormatArgImpl::Dispatch<short>(arg, short_str.size(), 0, arg);

  // Add a call to the function that was not called by the fuzz target.
  absl::str_format_internal::FormatArgImpl::Dispatch<short>(arg, short_str.size(), 0, arg);

  // Add a call to the function that was not called by the fuzz target.
  absl::str_format_internal::FormatArgImpl::Dispatch<short>(arg, short_str.size(), 0, arg);

  return 0;
}