#ifdef __cplusplus
extern "C" {
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int x, y, channels;

  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRemainingBytesAsString();

  if (!stbi_info(filename.c_str(), &x, &y, &channels))
    return 0;

  /* exit if the image is larger than ~80MB */
  if (y && x > (80000000 / 4) / y)
    return 0;

  unsigned char *img = stbi_load(filename.c_str(), &x, &y, &channels, 4);

  free(img);

  return 0;
}

#ifdef __cplusplus
}
#endif