#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int x, y, channels;
  struct stbi__context s;
  stbi__start_mem(&s, data, size);

  if (!stbi__jpeg_load_from_memory(&s, &x, &y, &channels, 4))
    return 0;

  /* exit if the image is larger than ~80MB */
  if (y && x > (80000000 / 4) / y)
    return 0;

  unsigned char *img = stbi__load_from_memory(&s, &x, &y, &channels, 4);

  free(img);

  return 0;
}

#ifdef __cplusplus
}
#endif