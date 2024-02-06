#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct buffer b;
  buffer_init(&b);

  while (stream.remaining_bytes() > 0) {
    // Define flags
    int flags = stream.ConsumeIntegral<int>();

    // Define len and str
    size_t len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    std::string str = stream.ConsumeBytesAsString(len);

    // Call the function
    burl_append(&b, str.data(), len, flags);
  }

  buffer_free(&b);

  return 0;
}