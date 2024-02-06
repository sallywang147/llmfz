#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRemainingBytesAsString();

  int result = stbi_is_16_bit(filename.c_str());

  return 0;
}

#ifdef __cplusplus
}
#endif