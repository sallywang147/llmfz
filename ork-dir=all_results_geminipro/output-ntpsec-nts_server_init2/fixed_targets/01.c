#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool nts_server_init2();

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_server.c
  return nts_server_init2();
}