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
  const std::string file_name = stream.ConsumeRemainingBytesAsString();
  int ret = png_image_read_colormapped(const_cast<char*>(file_name.c_str()));
  return ret;
}