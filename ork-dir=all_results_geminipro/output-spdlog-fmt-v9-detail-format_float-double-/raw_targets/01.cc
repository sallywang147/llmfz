#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include "fmt/format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  double value = provider.ConsumeFloatingPoint<double>();
  int precision = provider.ConsumeIntegralInRange<int>(0, 100);
  size_t width = provider.ConsumeIntegralInRange<size_t>(0, 100);

  std::vector<char> buffer(width);
  fmt::v9::detail::buffer<char> buf{buffer.data(), buffer.size()};

  fmt::v9::detail::format_float<double>(value, precision, width, &buf);

  return 0;
}