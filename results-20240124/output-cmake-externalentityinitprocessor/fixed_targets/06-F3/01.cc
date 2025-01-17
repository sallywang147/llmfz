#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#ifdef __cplusplus
}
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  xmlParserCtxtPtr parser = xmlCreateParserCtxt();
  if (!parser)
    return 0;

  char* context = (char*)malloc(size);
  if (!context) {
    xmlFreeParserCtxt(parser);
    return 0;
  }
  memcpy(context, data, size);

  xmlParseEntity(parser, context);
  free(context);
  xmlFreeParserCtxt(parser);
  return 0;
}