#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include "buf.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Buf *buf = buf_new(size);
  buf_append(buf, data, size);
  buf_prints(buf, "%s", buf->data);
  buf_free(buf);
  return 0;
}