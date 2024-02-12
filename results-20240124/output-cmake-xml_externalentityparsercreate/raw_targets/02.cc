 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char* context = NULL;
  char* base = NULL;
  XML_ParserStruct* parser = XML_ExternalEntityParserCreate(NULL, context, base);
  if (!parser) {
    return 0;
  }

  XML_Parse(parser, (const char*)data, size, 1);
  XML_ParserFree(parser);
  return 0;
}