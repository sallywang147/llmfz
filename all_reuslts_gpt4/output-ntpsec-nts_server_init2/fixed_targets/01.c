#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  // We don't need any input data for this function.
  // Just call the function and return.
  nts_server_init2();
  return 0;
}