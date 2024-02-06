#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "fuzzer/FuzzedDataProvider.h"
#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t initial_size = stream.ConsumeIntegral<size_t>();
  char* p = static_cast<char*>(std::malloc(initial_size));
  if (p == nullptr) {
    return 0;
  }
  Jbig2Allocator allocator = {};
  const size_t new_size = stream.ConsumeIntegral<size_t>();
  char* result = jbig2_default_realloc(&allocator, p, new_size);
  std::free(p);
  std::free(result);
  return 0;
}