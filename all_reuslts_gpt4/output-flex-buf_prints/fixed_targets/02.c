#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "buf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct Buf *buf = buf_new();
  if (buf == NULL) {
    return 0;
  }

  std::string fmt = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string s = stream.ConsumeRemainingBytesAsString();

  buf = buf_prints(buf, (char *)fmt.c_str(), (char *)s.c_str());

  buf_free(buf);

  return 0;
}