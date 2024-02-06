#ifdef __cplusplus
extern "C" {
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

unsigned char *load_jpeg_image(const char *filename, int *x, int *y, int *channels, int desired_channels) {
  int n;
  unsigned char *data = stbi_load(filename, x, y, &n, desired_channels);
  if (data == NULL) {
    return NULL;
  }
  *channels = n;
  return data;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int x, y, channels;

  if (!stbi_info_from_memory(data, size, &x, &y, &channels)) {
    return 0;
  }

  /* exit if the image is larger than ~80MB */
  if (y && x > (80000000 / 4) / y) {
    return 0;
  }

  unsigned char *img = load_jpeg_image(NULL, &x, &y, &channels, 4);

  if (img == NULL) {
    return 0;
  }

  free(img);

  return 0;
}

#ifdef __cplusplus
}
#endif