#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "scanner.h"
}

int main() {
  char *token;
  while ((token = scan_entity()) != NULL) {
    printf("%s\n", token);
    free(token);
  }
  return 0;
}