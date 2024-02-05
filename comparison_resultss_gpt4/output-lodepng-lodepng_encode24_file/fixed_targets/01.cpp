#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  if (stream.remaining_bytes() < 4)
    return 0;

  // Consume 4 bytes for width and height
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();

  // Consume the rest of the data for image
  std::string image = stream.ConsumeRemainingBytesAsString();
  
  // Call the function to fuzz
  lodepng_encode24_file("/dev/null", const_cast<char*>(image.c_str()), w, h);

  return 0;
}