#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();
  int colortype = stream.ConsumeIntegral<int>();
  int bitdepth = stream.ConsumeIntegral<int>();

  // Extract a string
  std::string filename = stream.ConsumeRandomLengthString();
  
  // Extract an array of bytes as a vector
  std::vector<char> in = stream.ConsumeRemainingBytes<char>();

  lodepng::encode(&filename, in.data(), w, h, colortype, bitdepth);

  return 0;
}