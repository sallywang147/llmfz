#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  llhttp__internal_t parser;
  llhttp__debug(&parser, (char*)data, (char*)data, (char*)data);
  return 0;
}