#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int w = stream.ConsumeIntegralInRange<int>(1, 4096);
  int h = stream.ConsumeIntegralInRange<int>(1, 4096);
  int bps = stream.ConsumeIntegralInRange<int>(1, 4);
  
  // Ensure that the input buffer size is exactly w * h * bps
  size_t in_size = w * h * bps;
  if (stream.remaining_bytes() < in_size) {
    return 0;
  }
  std::vector<char> in = stream.ConsumeBytes<char>(in_size);
  
  char* out = nullptr;
  size_t out_size = WebPEncodeLosslessBGR(in.data(), w, h, bps, &out);
  
  if (out_size > 0) {
    free(out);
  }

  return 0;
}