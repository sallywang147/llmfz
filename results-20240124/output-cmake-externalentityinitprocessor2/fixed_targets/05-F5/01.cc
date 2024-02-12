#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xmlparse.h"

extern "C" {
#include "expat.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser)
    return 0;

  char* buf = (char*)malloc(size);
  if (!buf) {
    XML_ParserFree(parser);
    return 0;
  }
  memcpy(buf, data, size);

  XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor2);
  XML_Parse(parser, buf, size, 1);
  free(buf);
  XML_ParserFree(parser);
  return 0;
}