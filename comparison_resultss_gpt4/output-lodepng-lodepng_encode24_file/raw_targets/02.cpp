#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string filename = stream.ConsumeRandomLengthString();
  std::string image = stream.ConsumeRemainingBytesAsString();

  // Width and height are set to 1 to make sure the image size is at least 3 bytes (RGB).
  // The actual image size may be larger, but lodepng_encode24_file will only read the first 3 bytes.
  int w = 1;
  int h = 1;

  lodepng_encode24_file(filename.c_str(), image.data(), w, h);

  return 0;
}