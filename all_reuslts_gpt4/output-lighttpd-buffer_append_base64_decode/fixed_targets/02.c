#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  struct buffer out;
  buffer_init(&out);
  
  size_t in_length = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string in = stream.ConsumeBytesAsString(in_length);
  int charset = stream.ConsumeIntegral<int>();

  buffer_append_base64_decode(&out, in.c_str(), in_length, charset);

  buffer_free(&out);
  return 0;
}