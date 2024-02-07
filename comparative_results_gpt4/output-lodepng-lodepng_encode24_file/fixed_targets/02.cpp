#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for the filename.
  std::string filename = stream.ConsumeRandomLengthString();
  char *filename_ptr = const_cast<char *>(filename.c_str());

  // Consume data for the image.
  std::string image = stream.ConsumeRemainingBytesAsString();
  char *image_ptr = const_cast<char *>(image.c_str());

  // Define the width and height.
  // To avoid overflow, we take the square root of the remaining size as the width and height.
  int w = sqrt(image.size());
  int h = w;

  // Call the target function.
  lodepng_encode24_file(filename_ptr, image_ptr, w, h);

  return 0;
}