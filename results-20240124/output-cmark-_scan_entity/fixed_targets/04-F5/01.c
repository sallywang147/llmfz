#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "scan_entity.h"
}

int main() {
  char *name = scan_entity("Enter your name: ");
  printf("Hello, %s!\n", name);
  free(name);
  return 0;
}