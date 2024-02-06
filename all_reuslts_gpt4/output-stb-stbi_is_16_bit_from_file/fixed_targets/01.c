#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  FILE *f = fmemopen((void *)str.c_str(), str.size(), "rb");
  if (!f) {
    return 0;
  }
  stbi_is_16_bit_from_file(f);
  fclose(f);
  return 0;
}