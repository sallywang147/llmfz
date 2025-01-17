#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data for parameters
  const int w = stream.ConsumeIntegralInRange<int>(1, 100);
  const int h = stream.ConsumeIntegralInRange<int>(1, 100);
  const int bps = stream.ConsumeIntegralInRange<int>(1, 100);

  // Calculate the size of the input image data
  const size_t in_size = w * h * bps;
  if (in_size > stream.remaining_bytes()) {
    return 0;
  }

  // Consume the data for the input image
  std::string in = stream.ConsumeBytesAsString(in_size);

  // Prepare the output parameter
  uint8_t* out = nullptr;

  // Call the function to fuzz
  const size_t out_size = WebPEncodeLosslessRGBA(in.c_str(), w, h, bps, (char **)&out);

  // Free the output buffer
  if (out != nullptr) {
    free(out);
  }

  return 0;
}