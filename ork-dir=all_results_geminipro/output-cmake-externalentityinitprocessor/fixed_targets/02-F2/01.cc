#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expat.h"

extern "C" {
#include "expat.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }
  XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor);
  XML_Status status = XML_Parse(parser, (const char *)data, size, 1);
  if (status != XML_STATUS_OK) {
    fprintf(stderr, "XML Parse error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
  }
  XML_ParserFree(parser);
  return 0;
}

int externalEntityInitProcessor(XML_Parser parser, const XML_Char *context,
                                const XML_Char *base, const XML_Char **systemId,
                                const XML_Char **publicId) {
  // Do nothing.
  return XML_STATUS_OK;
}