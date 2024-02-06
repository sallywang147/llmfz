#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  struct buffer out;
  buffer_init(&out);
  
  // Consume half of the data for 'in' parameter
  std::string in = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  
  // Consume an integer for 'charset' parameter
  int charset = stream.ConsumeIntegral<int>();
  
  // Call the function
  buffer_append_base64_decode(&out, const_cast<char*>(in.c_str()), in.size(), charset);
  
  buffer_free(&out);
  
  return 0;
}