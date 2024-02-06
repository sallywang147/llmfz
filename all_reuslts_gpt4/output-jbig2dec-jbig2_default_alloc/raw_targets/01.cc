#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  _Jbig2Allocator allocator;
  allocator.alloc = jbig2_default_alloc;
  allocator.free = jbig2_default_free;
  allocator.realloc = jbig2_default_realloc;

  size_t alloc_size = stream.ConsumeIntegral<size_t>();
  char* ptr = allocator.alloc(&allocator, alloc_size);

  if (ptr) {
    allocator.free(&allocator, ptr);
  }

  return 0;
}