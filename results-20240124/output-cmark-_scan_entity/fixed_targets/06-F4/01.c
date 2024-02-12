#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "scanner.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *token;
  while ((token = _scan_entity((char *)data)) != NULL) {
    printf("%s\n", token);
    free(token);
  }
  return 0;
}

int main() {
  char *token;
  while ((token = scan_entity()) != NULL) {
    printf("%s\n", token);
    free(token);
  }
  return 0;
}