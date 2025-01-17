#include <cstdint>
#include <cstring>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Jbig2Allocator allocator;

  allocator.alloc = NULL;
  allocator.free = jbig2_default_free;
  allocator.realloc = NULL;

  jbig2_default_free(&allocator, (char *)data);
  return 0;
}