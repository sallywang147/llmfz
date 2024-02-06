#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // We will use the first byte of the data as the width of the image
  int width = stream.ConsumeIntegral<uint8_t>();

  // We will use the second byte of the data as the height of the image
  int height = stream.ConsumeIntegral<uint8_t>();

  // We will use the rest of the data as the image
  std::string image = stream.ConsumeRemainingBytesAsString();

  // We will use a hardcoded filename for the output file
  char filename[] = "output.png";

  // Call the function under test
  lodepng_encode24_file(filename, const_cast<char *>(image.c_str()), width, height);

  return 0;
}