#include <cstdint>
#include <cstring>
#include <cstdio>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  auto stream = FuzzedDataProvider(data, size);
  size_t len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  auto text = stream.ConsumeBytes<char>(len);
  fmt::detail::print(stdout, text.data(), len);
  return 0;
}