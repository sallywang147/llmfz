#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

extern "C" {
#include "libxml/parserInternals.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  xmlParserCtxtPtr ctxt = xmlCreateFileParserCtxt(test_file);
  if (!ctxt)
    return 0;

  xmlParseDocument(ctxt);

  XML_ParserStruct *parser = ctxt->input->freeExternalEntities;
  XML_ExternalEntityParserCreate(parser, NULL, NULL);

  xmlFreeParserCtxt(ctxt);

  remove(test_file);
  return 0;
}