#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the allocator
  Jbig2Allocator allocator;
  allocator.alloc = (Jbig2AllocFn) malloc;
  allocator.free = (Jbig2FreeFn) free;
  allocator.realloc = (Jbig2ReallocFn) realloc;

  // Consume data for the size of the memory to be allocated
  size_t alloc_size = stream.ConsumeIntegral<size_t>();
  char* p = (char*) allocator.alloc(&allocator, alloc_size);

  // If allocation failed, return early
  if (p == nullptr) {
    return 0;
  }

  // Consume data for the size of the memory to be reallocated
  size_t realloc_size = stream.ConsumeIntegral<size_t>();
  p = jbig2_default_realloc(&allocator, p, realloc_size);

  // Free the memory
  allocator.free(&allocator, p);

  return 0;
}