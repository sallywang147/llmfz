 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xml.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser)
    return 0;

  char* context = (char*)malloc(size);
  if (!context) {
    XML_ParserFree(parser);
    return 0;
  }
  memcpy(context, data, size);

  externalEntityInitProcessor(parser, context, context, NULL);
  free(context);
  XML_ParserFree(parser);
  return 0;
}