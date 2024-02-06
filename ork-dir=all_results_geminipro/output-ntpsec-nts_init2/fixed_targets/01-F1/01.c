#include "ntpd.h"

extern "C" {
#include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  nts_init2();
  return 0;
}