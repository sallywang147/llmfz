#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "absl/strings/str_format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str_arg = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  char *arg = const_cast<char*>(str_arg.c_str());

  // Extract a string for the last parameter. You MUST use .c_str() to use result as pointer
  std::string str_last = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  char *last = const_cast<char*>(str_last.c_str());

  // Call the target function
  absl::str_format_internal::FormatArgImpl::Dispatch<long>(arg, spec, out, last);

  return 0;
}