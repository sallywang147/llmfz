#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  int64_t int_value = fuzzed_data.ConsumeIntegral<int64_t>();
  std::string int_str = absl::StrFormat("%ld", int_value);

  char arg[1024];
  char out[1024];
  size_t spec = fuzzed_data.ConsumeIntegralInRange<size_t>(0, 1024);
  bool result = absl::str_format_internal::FormatArgImpl::Dispatch<int64_t>(arg, spec, sizeof(out), out);
  if (!result)
    return 0;

  if (!absl::SimpleAtoi(out, &int_value))
    return 0;

  return 0;
}