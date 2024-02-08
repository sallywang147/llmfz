#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <llhttp.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  llhttp__internal_t parser;
  llhttp__init(&parser);
  llhttp__debug(&parser, (const char*)data, (const char*)(data + size), (const char*)data);
  llhttp__free(&parser);
  return 0;
}