#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "plist.h"
}

void plist_print(char * plist) {
  printf("%s\n", plist);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *plist = plist_parse(data, size);
  if (plist) {
    plist_print(plist);
    free(plist);
  }
  return 0;
}