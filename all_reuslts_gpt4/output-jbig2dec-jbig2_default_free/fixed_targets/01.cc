#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the _Jbig2Allocator struct
  _Jbig2Allocator allocator;
  allocator.alloc = NULL;
  allocator.free = NULL;
  allocator.realloc = NULL;

  // Consume the data as a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* p = const_cast<char*>(str.c_str());

  // Call the function to fuzz
  jbig2_default_free(&allocator, p);

  return 0;
}