#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t initial_size = stream.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
  char* p = static_cast<char*>(std::malloc(initial_size));
  const size_t new_size = stream.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
  Jbig2Allocator allocator = {};
  allocator.realloc = jbig2_default_realloc;
  char* result = allocator.realloc(&allocator, p, new_size);
  std::free(p);
  std::free(result);
  return 0;
}