#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int c = stream.ConsumeIntegral<int>();
  hoedown_buffer* buf = hoedown_buffer_new(size);
  hoedown_buffer_put_utf8(buf, c);
  hoedown_buffer_free(buf);
  return 0;
}