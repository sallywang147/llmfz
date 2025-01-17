#include <stdint.h>
#include <stdlib.h>
#include <string.h> // for memcpy

extern "C" {
#include <flex.h>
}

extern "C" char * yy_flex_xmalloc(int size) {
  char *ptr = (char *)malloc(size);
  if (!ptr) {
    exit(1);
  }
  return ptr;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  int size_fuzz = *(int *)data;
  if (size_fuzz < 0) {
    return 0;
  }
  data += 4;
  size -= 4;
  char *ptr = yy_flex_xmalloc(size_fuzz);
  memcpy(ptr, data, size);
  free(ptr);
  return 0;
}