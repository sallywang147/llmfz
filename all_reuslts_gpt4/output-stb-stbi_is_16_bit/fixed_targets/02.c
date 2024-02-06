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
  std::string filename = stream.ConsumeRemainingBytesAsString();
  // Ensure the string is null-terminated.
  filename.push_back('\0');

  // Call the function under test.
  int result = stbi_is_16_bit(const_cast<char*>(filename.c_str()));

  return 0;
}