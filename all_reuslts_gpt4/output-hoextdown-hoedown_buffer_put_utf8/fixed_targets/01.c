#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a hoedown_buffer
  hoedown_buffer *buf = hoedown_buffer_new(size);
  if (!buf)
    return 0;

  // Consume the data and put it into the buffer
  while (stream.remaining_bytes() > 0) {
    int c = stream.ConsumeIntegral<int>();
    hoedown_buffer_put_utf8(buf, c);
  }

  // Clean up
  hoedown_buffer_free(buf);

  return 0;
}