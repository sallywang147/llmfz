#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buf.h"

extern "C" {
#include "buf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Buf *buf = buf_new(size);
  if (!buf) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  char *fmt = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();
  char *s = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();
  buf_prints(buf, fmt, s);
  buf_free(buf);
  return 0;
}