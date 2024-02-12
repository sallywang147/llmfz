#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "expat.h"

extern "C" {
#include "expat.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char* public_id = (char*)malloc(size);
  memcpy(public_id, data, size);

  char* system_id = (char*)malloc(size);
  memcpy(system_id, data, size);

  char* base = (char*)malloc(size);
  memcpy(base, data, size);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser)
    return 0;

  if (XML_SetParamEntityParsing(parser, XML_PARAM_ENTITY_PARSING_ALWAYS)) {
    if (XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor)) {
      XML_Parse(parser, NULL, 0, XML_FALSE);
    }
  }

  XML_ParserFree(parser);
  free(public_id);
  free(system_id);
  free(base);

  return 0;
}