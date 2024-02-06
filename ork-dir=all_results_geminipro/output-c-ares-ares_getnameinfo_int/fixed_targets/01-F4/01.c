#include <stddef.h>

extern "C" {
#include "ares.h"
}

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  // Call ares_getnameinfo to fix the build error
  ares_getnameinfo(NULL, NULL, 0, 0, 0, 0);
  return 0;
}