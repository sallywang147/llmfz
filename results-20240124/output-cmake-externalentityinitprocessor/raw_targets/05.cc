 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char* buf = (char*)malloc(size);
  if (!buf)
    return 0;
  memcpy(buf, data, size);
  char* base = buf;
  char* sysid = buf;
  char* pubid = buf;
  char* context = buf;
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser)
    return 0;

  XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor);
  int ret = XML_Parse(parser, base, size, 1);
  if (ret == XML_STATUS_ERROR) {
    printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
  }

  XML_ParserFree(parser);
  free(buf);
  return 0;
}