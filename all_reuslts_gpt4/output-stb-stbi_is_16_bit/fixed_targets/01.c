#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string filename = stream.ConsumeRandomLengthString();
  FILE *file = fopen(filename.c_str(), "wb");
  if (!file) {
    return 0;
  }

  std::vector<uint8_t> remaining_bytes = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(remaining_bytes.data(), 1, remaining_bytes.size(), file);
  fclose(file);

  stbi_is_16_bit(filename.c_str());

  remove(filename.c_str());

  return 0;
}