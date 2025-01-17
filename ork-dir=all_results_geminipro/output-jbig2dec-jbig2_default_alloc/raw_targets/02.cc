#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  Jbig2Allocator allocator;

  allocator.alloc = jbig2_default_alloc;
  allocator.free = free;
  allocator.realloc = realloc;

  jbig2_default_alloc(&allocator, size);

  return 0;
}