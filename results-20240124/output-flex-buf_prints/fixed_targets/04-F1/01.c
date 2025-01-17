#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "buf.h"

extern "C" {
#include "buf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  struct Buf* buf = buf_new(size);
  buf_prints(buf, (char*)data, (char*)data + 1);
  buf_free(buf);
  return 0;
}