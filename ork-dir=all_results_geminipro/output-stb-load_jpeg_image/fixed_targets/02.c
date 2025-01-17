#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int x, y, channels;
  unsigned char *img = stbi_load_from_memory(data, size, &x, &y, &channels, 4);
  free(img);
  return 0;
}

char *load_jpeg_image(struct stbi__jpeg *z, int *out_x, int *out_y, int *comp, int req_comp) {
  return NULL;
}

#ifdef __cplusplus
}
#endif