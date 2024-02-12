#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libxml/parser.h"

extern "C" {
#include "libxml/parserInternals.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  xmlDocPtr doc = xmlReadMemory((const char*)data, size, NULL, NULL, 0);
  if (!doc)
    return 0;
  xmlFreeDoc(doc);

  xmlParserCtxtPtr ctxt = xmlNewParserCtxt();
  if (!ctxt)
    return 0;
  xmlParseDocument(ctxt, (const char*)data);
  xmlFreeParserCtxt(ctxt);

  xmlParserReset(ctxt, (const char*)data);
  xmlParseDocument(ctxt, (const char*)data);
  xmlFreeParserCtxt(ctxt);

  xmlParserCtxtPtr ctxt2 = xmlNewParserCtxt();
  if (!ctxt2)
    return 0;
  xmlParseDocument(ctxt2, (const char*)data);
  xmlFreeParserCtxt(ctxt2);

  // Call the target function
  char *buffer = (char*)malloc(size);
  memcpy(buffer, data, size);
  XML_ParserReset(ctxt2, buffer);
  free(buffer);

  return 0;
}