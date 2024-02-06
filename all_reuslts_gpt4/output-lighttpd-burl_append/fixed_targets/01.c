#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the buffer
  struct buffer b;
  buffer_init(&b);

  // Extract a string
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = str.c_str();

  // Extract the length of the string
  size_t len = str.length();

  // Extract flags
  int flags = stream.ConsumeIntegral<int>();

  // Call the function
  burl_append(&b, ptr, len, flags);

  // Free the buffer
  buffer_free(&b);

  return 0;
}