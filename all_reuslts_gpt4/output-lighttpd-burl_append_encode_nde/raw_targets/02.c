#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize buffer
  struct buffer *b = buffer_new();

  // Extract a string
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Call the function under test
  burl_append_encode_nde(b, ptr, str.size());

  // Clean up
  buffer_free(b);

  return 0;
}