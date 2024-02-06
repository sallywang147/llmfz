#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int x, y, channels;
  char *img = load_jpeg_image(NULL, &x, &y, &channels, 4);
  free(img);
  return 0;
}

#ifdef __cplusplus
}
#endif