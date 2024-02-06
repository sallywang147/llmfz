#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  const int w = stream.ConsumeIntegralInRange<int>(1, 4096);
  const int h = stream.ConsumeIntegralInRange<int>(1, 4096);
  const int bps = stream.ConsumeIntegralInRange<int>(1, 4);

  // Calculate the number of bytes needed for the input image.
  const size_t in_size = static_cast<size_t>(w) * h * bps;
  if (in_size > stream.remaining_bytes()) {
    return 0;
  }

  std::vector<char> in = stream.ConsumeBytes<char>(in_size);
  char* out = nullptr;

  WebPEncodeLosslessBGR(in.data(), w, h, bps, &out);

  if (out != nullptr) {
    free(out);
  }

  return 0;
}