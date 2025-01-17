#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string filename = stream.ConsumeRandomLengthString();
  std::string image = stream.ConsumeRemainingBytesAsString();

  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();

  lodepng_encode24_file(filename.c_str(), image.c_str(), w, h);

  return 0;
}