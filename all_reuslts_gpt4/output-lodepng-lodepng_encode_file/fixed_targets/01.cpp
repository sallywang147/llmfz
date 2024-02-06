#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for filename. We use a small max size to avoid excessively long filenames.
  std::string filename = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100));
  
  // Extract a string for image data.
  std::string image = stream.ConsumeBytesAsString(stream.remaining_bytes());

  // Extract integral values for width, height, colortype and bitdepth
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();
  int colortype = stream.ConsumeIntegral<int>();
  int bitdepth = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  lodepng_encode_file(const_cast<char*>(filename.c_str()), const_cast<char*>(image.c_str()), w, h, colortype, bitdepth);

  return 0;
}