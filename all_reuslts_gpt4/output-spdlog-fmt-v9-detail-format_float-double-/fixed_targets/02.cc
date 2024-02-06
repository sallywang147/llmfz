#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <fmt/format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  double value = fuzzed_data.ConsumeFloatingPoint<double>();
  int precision = fuzzed_data.ConsumeIntegral<int>();
  size_t buffer_size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, 1024);

  fmt::v9::detail::buffer<char> buffer;
  buffer.resize(buffer_size);

  fmt::v9::detail::format_float<double>(value, precision, buffer_size, &buffer);

  return 0;
}