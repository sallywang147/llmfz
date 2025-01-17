#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buf.h"

extern "C" {
#include "llvm/Support/Format.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Buf *buf = buf_new(size);
  if (buf == NULL) {
    return 0;
  }
  buf_resetw(buf);

  const char *fmt = (const char *)data;
  size_t fmt_len = strnlen((const char *)data, size);
  buf_puts(buf, fmt, fmt_len);

  const char *s = (const char *)(data + fmt_len);
  size_t s_len = size - fmt_len;
  buf_puts(buf, s, s_len);

  buf_prints(buf, "%s", buf->buf);

  buf_free(buf);
  return 0;
}