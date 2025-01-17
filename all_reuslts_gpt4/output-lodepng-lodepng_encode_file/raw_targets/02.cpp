#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract filename
  std::string filename = stream.ConsumeRandomLengthString();
  char *filename_ptr = const_cast<char *>(filename.c_str());

  // Extract image
  std::string image = stream.ConsumeRandomLengthString();
  char *image_ptr = const_cast<char *>(image.c_str());

  // Extract width and height
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();

  // Extract colortype and bitdepth
  int colortype = stream.ConsumeIntegral<int>();
  int bitdepth = stream.ConsumeIntegral<int>();

  // Call the target function
  lodepng_encode_file(filename_ptr, image_ptr, w, h, colortype, bitdepth);

  return 0;
}