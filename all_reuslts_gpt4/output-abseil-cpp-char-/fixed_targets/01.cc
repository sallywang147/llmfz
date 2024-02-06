#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "absl/strings/str_format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Consume data for the parameters
  std::string arg = provider.ConsumeRandomLengthString();
  size_t spec = provider.ConsumeIntegral<size_t>();
  int out = provider.ConsumeIntegral<int>();
  std::string out_string = provider.ConsumeRandomLengthString();

  // Call the function under test
  bool result = absl::str_format_internal::FormatArgImpl::Dispatch<signed char>(const_cast<char*>(arg.c_str()), spec, out, const_cast<char*>(out_string.c_str()));

  return 0;
}