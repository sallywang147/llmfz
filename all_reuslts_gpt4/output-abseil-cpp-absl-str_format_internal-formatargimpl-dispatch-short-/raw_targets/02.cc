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
  std::string str = stream.ConsumeRandomLengthString();
  char *arg = const_cast<char*>(str.c_str());

  // Create an instance of FormatArgImpl
  absl::str_format_internal::FormatArgImpl format_arg_impl;

  // Call the function
  bool result = format_arg_impl.Dispatch<short>(arg, spec, out, nullptr);

  return 0;
}