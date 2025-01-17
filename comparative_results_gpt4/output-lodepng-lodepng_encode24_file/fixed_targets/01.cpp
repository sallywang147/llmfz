#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

#include "lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract a string to use as filename. We use a temporary file to avoid any file system side effects.
  std::string filename = "/tmp/" + stream.ConsumeRandomLengthString();
  
  // Extract a string to use as image data.
  std::string image = stream.ConsumeRemainingBytesAsString();

  // Use the last two bytes of the input as width and height.
  int w = static_cast<int>(data[size - 2]);
  int h = static_cast<int>(data[size - 1]);

  // Call the function under test.
  lodepng_encode24_file(const_cast<char*>(filename.c_str()), const_cast<char*>(image.c_str()), w, h);

  return 0;
}