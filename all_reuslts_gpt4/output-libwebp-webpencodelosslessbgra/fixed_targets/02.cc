#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  const int w = provider.ConsumeIntegralInRange<int>(1, 100);
  const int h = provider.ConsumeIntegralInRange<int>(1, 100);
  const int bps = provider.ConsumeIntegralInRange<int>(1, 4);

  if (w * h * bps > provider.remaining_bytes()) {
    return 0;
  }

  std::vector<char> in = provider.ConsumeBytes<char>(w * h * bps);

  char* out = nullptr;
  size_t out_size = WebPEncodeLosslessBGRA(in.data(), w, h, bps, &out);

  if (out_size > 0 && out != nullptr) {
    free(out);
  }

  return 0;
}