#include "lodepng.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for parameters
  std::string filename = stream.ConsumeRandomLengthString();
  std::string image = stream.ConsumeRemainingBytesAsString();
  int w = stream.ConsumeIntegral<int>();
  int h = stream.ConsumeIntegral<int>();

  // Call the function
  lodepng_encode32_file(const_cast<char*>(filename.c_str()), const_cast<char*>(image.c_str()), w, h);

  return 0;
}