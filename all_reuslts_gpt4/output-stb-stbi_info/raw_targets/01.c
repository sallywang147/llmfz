#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string filename = stream.ConsumeRandomLengthString();
  int x, y, comp;

  // Call the function to fuzz
  stbi_info(const_cast<char*>(filename.c_str()), &x, &y, &comp);

  return 0;
}