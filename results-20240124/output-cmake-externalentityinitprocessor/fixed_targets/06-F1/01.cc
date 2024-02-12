#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <libxml/parser.h>

#ifdef __cplusplus
}
#endif

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