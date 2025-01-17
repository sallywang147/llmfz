#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fmt/format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  double double_arg = stream.ConsumeFloatingPoint<double>();
  int int_arg = stream.ConsumeIntegral<int>();
  size_t size_arg = stream.ConsumeIntegral<size_t>();
  
  fmt::memory_buffer buf;
  
  fmt::v9::detail::format_float<double>(double_arg, int_arg, size_arg, &buf);
  
  return 0;
}