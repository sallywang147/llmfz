#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "buffer.h"

extern "C" {
#include "hoedown.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t buffer_size = stream.ConsumeIntegral<uint8_t>();
  hoedown_buffer* buffer = hoedown_buffer_new(buffer_size);
  if (buffer == nullptr) {
    return 0;
  }

  const uint32_t codepoint = stream.ConsumeIntegral<uint32_t>();
  hoedown_buffer_put_utf8(buffer, codepoint);
  hoedown_buffer_free(buffer);
  return 0;
}