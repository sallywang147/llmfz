#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <string>

namespace {
// Amount of valid colortype/bidthdepth combinations in the PNG file format.
const size_t num_combinations = 15;

LodePNGColorType colortypes[num_combinations] = {
    LCT_GREY,       LCT_GREY,       LCT_GREY,    LCT_GREY,    LCT_GREY, // 1, 2, 4, 8 or 16 bits
    LCT_RGB,        LCT_RGB,                                            // 8 or 16 bits
    LCT_PALETTE,    LCT_PALETTE,    LCT_PALETTE, LCT_PALETTE,           // 1, 2, 4 or 8 bits
    LCT_GREY_ALPHA, LCT_GREY_ALPHA,                                     // 8 or 16 bits
    LCT_RGBA,       LCT_RGBA,                                           // 8 or 16 bits
};

unsigned bitdepths[num_combinations] = {
    1, 2,  4, 8, 16, // gray
    8, 16,           // rgb
    1, 2,  4, 8,     // palette
    8, 16,           // gray+alpha
    8, 16,           // rgb+alpha
};
} // end anonymous namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Get random color type and bit depth
  size_t random_color_type = stream.ConsumeIntegralInRange<size_t>(0, num_combinations - 1);
  LodePNGColorType colortype = colortypes[random_color_type];
  unsigned bitdepth = bitdepths[random_color_type];

  // Consume some bytes for the filename
  std::string filename = stream.ConsumeRandomLengthString();
  // Consume remaining bytes for the image data
  std::string in = stream.ConsumeRemainingBytesAsString();

  // Use a small constant for width and height for simplicity
  int w = 10;
  int h = 10;

  // Call the function to be fuzzed
  lodepng::encode(&filename, (char *)in.data(), w, h, colortype, bitdepth);

  return 0;
}