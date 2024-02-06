#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize buffer
  struct buffer buf;
  buffer_init(&buf);
  
  // Consume data for the string to be encoded
  std::string str = stream.ConsumeRemainingBytesAsString();
  
  // Call the function to be fuzzed
  burl_append_encode_nde(&buf, str.data(), str.size());
  
  // Clean up
  buffer_free(&buf);
  
  return 0;
}