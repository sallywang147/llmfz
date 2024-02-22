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
  const char *fmt = "%s";
  buf_prints(buf, (char *)fmt, (const char *)data);
  buf_free(buf);
  return 0;
}