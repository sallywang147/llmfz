#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void nts_init2();

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  nts_init2();
  return 0;
}