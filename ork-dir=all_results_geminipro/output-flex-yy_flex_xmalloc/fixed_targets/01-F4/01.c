#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" {
#include "flexdef.h"
}

extern "C" char *yy_flex_xmalloc(int size) {
  return static_cast<char *>(malloc(size));
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  int alloc_size = *(reinterpret_cast<const int *>(data));
  data += sizeof(int);
  size -= sizeof(int);
  char *buf = yy_flex_xmalloc(alloc_size);
  if (buf == nullptr) {
    return 0;
  }
  memcpy(buf, data, size);
  free(buf);
  return 0;
}