#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  const int width = provider.ConsumeIntegralInRange<int>(1, 4096);
  const int height = provider.ConsumeIntegralInRange<int>(1, 4096);
  const int bps = provider.ConsumeIntegralInRange<int>(1, 4);
  const float quality = provider.ConsumeFloatingPointInRange<float>(0.0, 100.0);

  const size_t in_size = width * height * bps;
  if (in_size > provider.remaining_bytes()) {
    return 0;
  }

  std::vector<char> in_buf = provider.ConsumeBytes<char>(in_size);
  char* in = in_buf.data();

  char* out = nullptr;

  WebPEncodeBGRA(in, width, height, bps, quality, &out);

  if (out != nullptr) {
    free(out);
  }

  return 0;
}