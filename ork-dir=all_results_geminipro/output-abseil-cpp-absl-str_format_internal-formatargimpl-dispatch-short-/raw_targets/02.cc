#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  short short_value = fuzzed_data.ConsumeIntegral<short>();
  std::string short_str = absl::StrFormat("%d", short_value);

  char arg[32];
  char out[32];
  bool result =
      absl::str_format_internal::FormatArgImpl::Dispatch<short>(
          arg, short_str.size(), short_value, out);
  if (!result)
    return 0;

  return 0;
}