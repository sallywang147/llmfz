#include <stddef.h>
#include <stdint.h>

#include "api/yajl_buf.h"

#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume data for parameters
  std::string str = stream.ConsumeRandomLengthString();
  int htmlSafe = stream.ConsumeBool();
  
  // Create buffer
  yajl_buf buf = yajl_buf_alloc(NULL);
  
  // Call the function
  yajl_string_encode(buf, (char*)str.c_str(), str.size(), htmlSafe);
  
  // Free the buffer
  yajl_buf_free(buf);
  
  return 0;
}