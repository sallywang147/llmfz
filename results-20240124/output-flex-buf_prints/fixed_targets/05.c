#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "buf.h"
}

static int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Buf *buf = buf_new(size);
  if (!buf) {
    return 0;
  }
  buf_append(buf, data, size);
  buf_prints(buf, "%s", buf->data);
  buf_free(buf);
  return 0;
}