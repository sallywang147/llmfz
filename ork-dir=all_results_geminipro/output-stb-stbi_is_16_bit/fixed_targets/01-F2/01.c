#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4)
    return 0;
  char filename[256];
  snprintf(filename, sizeof(filename), "/tmp/stb_image_fuzzer_XXXXXX");
  int fd = mkstemp(filename);
  if (fd == -1)
    return 0;
  write(fd, data, size);
  close(fd);

  int result = stbi_is_16_bit(filename);

  unlink(filename);

  return result;
}

#ifdef __cplusplus
}
#endif