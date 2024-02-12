 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *fmt = stream.ConsumeRandomLengthString().c_str();
  char *s = stream.ConsumeRemainingBytesAsString().c_str();
  struct Buf *buf = buf_new(10);
  buf_prints(buf, fmt, s);
  buf_free(buf);
  return 0;
}