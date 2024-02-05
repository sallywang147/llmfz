#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <string>
#include <vector>

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

  // Consume data for filename, image data, width, height, color type and bit depth
  std::string filename = stream.ConsumeRandomLengthString();
  std::string in = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();
  int colortype = stream.ConsumeIntegralInRange<int>(0, num_combinations - 1);
  int bitdepth = stream.ConsumeIntegral<int>();

  // Call the target function
  lodepng::encode(&filename, const_cast<char*>(in.c_str()), w, h, colortypes[colortype], bitdepth);

  return 0;
}