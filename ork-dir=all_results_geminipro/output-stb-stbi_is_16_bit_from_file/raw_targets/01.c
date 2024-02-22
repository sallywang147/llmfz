#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FILE *f = fmemopen(data, size, "rb");

  int result = stbi_is_16_bit_from_file(f);

  fclose(f);

  return 0;
}

#ifdef __cplusplus
}
#endif