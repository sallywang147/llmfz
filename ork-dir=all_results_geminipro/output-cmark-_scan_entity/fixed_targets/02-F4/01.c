#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "htmlparser.h"

extern "C" {
#include "scanentities.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *copy = (char *)malloc(size + 1);
  memcpy(copy, data, size);
  copy[size] = '\0';

  _scan_entity(copy);  // Fix: call _scan_entity instead of scan_entity

  free(copy);
  return 0;
}