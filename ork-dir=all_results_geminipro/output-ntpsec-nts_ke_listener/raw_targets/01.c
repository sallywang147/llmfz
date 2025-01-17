#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * nts_ke_listener(char * arg);

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_ke.c

  char *arg = (char *)malloc(Size + 1);
  memcpy(arg, Data, Size);
  arg[Size] = '\0';

  nts_ke_listener(arg);

  free(arg);

  return 0;
}