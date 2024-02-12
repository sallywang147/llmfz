#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <string.h>
}

extern "C" char * yy_flex_xmalloc(int size) {
  char *ptr = (char *)malloc(size);
  return ptr;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  int size_fuzz = 0;
  memcpy(&size_fuzz, data, 4);
  yy_flex_xmalloc(size_fuzz);
  return 0;
}