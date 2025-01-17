#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Extract a string for filename
  std::string filename = stream.ConsumeRandomLengthString();
  // Extract a string for input data
  std::string in = stream.ConsumeRemainingBytesAsString();

  // Extract integral values for width, height, colortype, bitdepth
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();
  int colortype = stream.ConsumeIntegral<int>();
  int bitdepth = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  lodepng::encode(&filename, in.c_str(), w, h, colortype, bitdepth);

  return 0;
}