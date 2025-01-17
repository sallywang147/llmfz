#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_lib.h"

extern "C" {
#include "parse_complex_format.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *ns = malloc(size + 1);
  memcpy(ns, data, size);
  ns[size] = '\0';

  parse_complex_format_second(ns);

  free(ns);
  return 0;
}