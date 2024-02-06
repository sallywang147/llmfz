#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int x, y, channels;

  if (!stbi_info_from_memory(data, size, &x, &y, &channels))
    return 0;

  /* exit if the image is larger than ~80MB */
  if (y && x > (80000000 / 4) / y)
    return 0;

  struct stbi__context s;
  stbi__start_mem(&s, data, size);
  unsigned char *img = stbi__jpeg_load(&s, &x, &y, &channels, 4, NULL);

  free(img);

  return 0;
}

#ifdef __cplusplus
}
#endif