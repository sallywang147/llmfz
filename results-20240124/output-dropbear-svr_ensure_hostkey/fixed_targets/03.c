#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mpfr.h>
#include <gmp.h>

extern "C" {
#include <libssh/libssh.h>
}

void svr_ensure_hostkey() {
  // ...
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  svr_ensure_hostkey();
  // ...
  return 0;
}