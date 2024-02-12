 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t count = provider.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<char> buffer(count);
  provider.ConsumeBytes(buffer.data(), count);
  fmt::detail::fwrite_fully(buffer.data(), count, stdout);
  return 0;
}