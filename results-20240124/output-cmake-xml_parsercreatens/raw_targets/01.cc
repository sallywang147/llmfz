 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char *buffer = (char*)malloc(size + 1);
  memcpy(buffer, data, size);
  buffer[size] = 0;

  XML_Parser parser = XML_ParserCreateNS(nullptr, ' ');
  XML_Parse(parser, buffer, size, 1);
  XML_ParserFree(parser);

  free(buffer);
  return 0;
}