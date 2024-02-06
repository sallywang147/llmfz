#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int x, y, channels;
  char filename[256];
  snprintf(filename, sizeof(filename), "/tmp/stb_image_fuzz_%d", rand());
  FILE *fp = fopen(filename, "wb");
  fwrite(data, size, 1, fp);
  fclose(fp);

  if (!stbi_info(filename, &x, &y, &channels))
    return 0;

  /* exit if the image is larger than ~80MB */
  if (y && x > (80000000 / 4) / y)
    return 0;

  unsigned char *img = stbi_load(filename, &x, &y, &channels, 4);

  free(img);

  return 0;
}

#ifdef __cplusplus
}
#endif