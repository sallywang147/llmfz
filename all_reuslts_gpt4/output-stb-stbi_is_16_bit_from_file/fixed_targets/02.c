#include <fuzzer/FuzzedDataProvider.h>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  const std::string tmp_name = "/tmp/fuzzed_file";
  FILE* fp = fopen(tmp_name.c_str(), "wb");
  if (!fp) {
    return 0;
  }
  
  std::vector<uint8_t> fuzzed_file = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(fuzzed_file.data(), 1, fuzzed_file.size(), fp);
  fclose(fp);

  fp = fopen(tmp_name.c_str(), "rb");
  if (!fp) {
    return 0;
  }

  stbi_is_16_bit_from_file(fp);
  fclose(fp);
  
  remove(tmp_name.c_str());

  return 0;
}