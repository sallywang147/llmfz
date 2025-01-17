#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "flexdef.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  int size_to_alloc = data[0];
  if (size_to_alloc < 0) {
    return 0;
  }
  char *ptr = yy_flex_xmalloc(size_to_alloc);
  if (ptr == nullptr) {
    return 0;
  }
  free(ptr);
  return 0;
}