#include <cstdio>
#include "buf.h"

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

struct Buf *buf_prints(struct Buf *buf, char *fmt, char *s) {
  return buf_printf(buf, fmt, s);
}

DEFINE_FUZZER(LLVMFuzzerTestOneInput) {
  struct Buf *buf = buf_new(1024);
  buf_prints(buf, "%s", data);
  buf_free(buf);
}