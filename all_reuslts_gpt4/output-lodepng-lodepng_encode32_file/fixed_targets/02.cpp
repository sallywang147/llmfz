#include <fuzzer/FuzzedDataProvider.h>
#include "lodepng.h"

#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Define FuzzedDataProvider
  FuzzedDataProvider stream(data, size);

  // Extract a string for filename
  std::string filename = stream.ConsumeRandomLengthString();
  
  // Extract a string for image
  std::string image = stream.ConsumeRemainingBytesAsString();

  // Extract integers for width and height
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  lodepng_encode32_file(const_cast<char*>(filename.c_str()), const_cast<char*>(image.c_str()), w, h);

  return 0;
}