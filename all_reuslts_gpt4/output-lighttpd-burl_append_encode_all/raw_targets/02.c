#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct buffer b;
  buffer_init(&b);

  size_t len = stream.remaining_bytes() / 2;
  std::string str = stream.ConsumeBytesAsString(len);

  burl_append_encode_all(&b, str.c_str(), len);

  buffer_free(&b);

  return 0;
}