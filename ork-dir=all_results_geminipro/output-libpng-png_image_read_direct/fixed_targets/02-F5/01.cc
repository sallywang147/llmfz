#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "png.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* input_cstr = const_cast<char*>(input.c_str());
  png_image image;
  png_image_read_from_memory(&image, input_cstr, input.size());
  png_image_free(&image);
  return 0;
}