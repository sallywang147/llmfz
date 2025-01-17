#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data for the parameters.
  int w = stream.ConsumeIntegralInRange<int>(0, 100);
  int h = stream.ConsumeIntegralInRange<int>(0, 100);
  int bps = stream.ConsumeIntegralInRange<int>(0, 100);

  // The input data for the function.
  std::vector<char> in = stream.ConsumeRemainingBytes<char>();
  char* out = nullptr;

  // Call the function.
  WebPEncodeLosslessRGB(in.data(), w, h, bps, &out);

  // Free the memory allocated by the function.
  free(out);

  return 0;
}