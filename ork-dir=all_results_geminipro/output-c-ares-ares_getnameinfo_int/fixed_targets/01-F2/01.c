#include <stddef.h>

extern "C" {
#include "ares.h"
}

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  // Call ares_getnameinfo_int to fix the build error