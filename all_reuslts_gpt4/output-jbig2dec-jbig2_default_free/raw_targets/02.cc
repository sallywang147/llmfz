#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize a Jbig2Allocator
  Jbig2Allocator allocator;
  allocator.alloc = NULL;
  allocator.free = NULL;
  allocator.realloc = NULL;

  // Consume some bytes from the stream to use as our char pointer
  std::string str = stream.ConsumeRandomLengthString();
  char* p = const_cast<char*>(str.c_str());

  // Call the function under test
  jbig2_default_free(&allocator, p);

  return 0;
}