#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "Platform_fp.h"
}

int RegularCommandService(int *PortNumber) {
  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  int PortNumber = 0;
  RegularCommandService(&PortNumber);
  return 0;
}