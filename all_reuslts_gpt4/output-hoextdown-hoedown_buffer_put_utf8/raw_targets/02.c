#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hoedown.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  hoedown_buffer* buf = hoedown_buffer_new(64);
  if (buf == nullptr) {
    return 0;
  }
  
  while (stream.remaining_bytes() > 0) {
    int c = stream.ConsumeIntegral<int>();
    hoedown_buffer_put_utf8(buf, c);
  }
  
  hoedown_buffer_free(buf);

  return 0;
}