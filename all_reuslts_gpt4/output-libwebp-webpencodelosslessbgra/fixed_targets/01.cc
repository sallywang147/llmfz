#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int w = stream.ConsumeIntegralInRange<int>(1, 4096);
  int h = stream.ConsumeIntegralInRange<int>(1, 4096);
  int bps = stream.ConsumeIntegralInRange<int>(1, 4);
  size_t in_size = static_cast<size_t>(w) * h * bps;

  if (in_size > stream.remaining_bytes()) {
    return 0;
  }

  std::vector<char> in = stream.ConsumeBytes<char>(in_size);
  char* out;

  WebPEncodeLosslessBGRA(in.data(), w, h, bps, &out);

  if (out != nullptr) {
    free(out);
  }

  return 0;
}