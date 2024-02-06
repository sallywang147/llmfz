#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the buffer struct
  struct buffer buf;
  buffer_init(&buf);

  // Extract a string from the data
  std::string str = stream.ConsumeRandomLengthString();
  char* str_ptr = const_cast<char*>(str.c_str());
  size_t len = str.size();

  // Call the target function
  burl_append_encode_psnde(&buf, str_ptr, len);

  // Clean up
  buffer_free(&buf);

  return 0;
}