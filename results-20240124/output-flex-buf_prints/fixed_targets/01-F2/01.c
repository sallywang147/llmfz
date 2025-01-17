#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "buf.h"

extern "C" {
#include "buf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Buf *buf = buf_new(100);
  if (!buf) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  const char *fmt = stream.ConsumeRandomLengthString(100).c_str();
  const char *s = stream.ConsumeRandomLengthString(100).c_str();
  buf_printf(buf, fmt, s);
  buf_free(buf);
  return 0;
}