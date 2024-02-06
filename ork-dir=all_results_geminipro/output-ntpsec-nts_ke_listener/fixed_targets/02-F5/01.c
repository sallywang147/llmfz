#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMinInputLength 20
#define kMaxInputLength 1024

char * nts_ke_listener(char * arg);

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_ke.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  char *arg = (char *)malloc(Size + 1);
  memcpy(arg, Data, Size);
  arg[Size] = '\0';

  char *ret = nts_ke_listener(arg);
  if (ret) free(ret);
  free(arg);

  return 0;
}

char * nts_ke_listener(char * arg) {
  // Function implementation
  return arg;
}