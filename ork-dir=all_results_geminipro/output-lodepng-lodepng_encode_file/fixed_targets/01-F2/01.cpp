#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "lodepng.h"

extern "C" {
#include "lodepng.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRandomLengthString();
  const std::vector<uint8_t> image = stream.ConsumeRemainingBytes<uint8_t>();
  const uint32_t w = stream.ConsumeIntegral<uint32_t>();
  const uint32_t h = stream.ConsumeIntegral<uint32_t>();
  const LodePNGColorType colortype =
      stream.PickValueInArray({LCT_GREY, LCT_RGB, LCT_PALETTE, LCT_GREY_ALPHA,
                               LCT_RGBA});
  const uint32_t bitdepth = stream.ConsumeIntegralInRange<uint32_t>(1, 16);
  int error = lodepng_encode_file(filename.c_str(), image.data(), w, h, colortype,
                                  bitdepth);
  if (error != 0) {
    return 0;
  }
  return 0;
}