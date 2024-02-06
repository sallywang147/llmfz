#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "jbig2.h"

struct _Jbig2Allocator {
  void *(*alloc)(struct _Jbig2Allocator *allocator, size_t size);
  void (*free)(struct _Jbig2Allocator *allocator, void *p);
  void *(*realloc)(struct _Jbig2Allocator *allocator, void *p, size_t size);
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the allocator
  struct _Jbig2Allocator allocator;
  allocator.alloc = malloc;
  allocator.free = free;
  allocator.realloc = realloc;

  // Consume a size for the initial allocation
  size_t initial_size = stream.ConsumeIntegralInRange<size_t>(0, size);

  // Allocate initial memory
  char* p = (char*)allocator.alloc(&allocator, initial_size);

  if (p == nullptr) {
    return 0;
  }

  // Consume a size for the reallocation
  size_t realloc_size = stream.ConsumeIntegralInRange<size_t>(0, size);

  // Reallocate memory
  p = jbig2_default_realloc(&allocator, p, realloc_size);

  // Free the memory
  allocator.free(&allocator, p);

  return 0;
}