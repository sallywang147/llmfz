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

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<char> arg = stream.ConsumeBytes<char>(stream.remaining_bytes());
  char *arg_ptr = arg.data();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *str_ptr = const_cast<char*>(str.c_str());

  // Call the target function
  bool result = absl::str_format_internal::FormatArgImpl::Dispatch<short>(arg_ptr, spec, out, str_ptr);

  return 0;
}