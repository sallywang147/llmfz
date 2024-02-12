#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"
#include "libxml/parserInternals.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  xmlParserCtxtPtr ctxt = xmlCreateParserCtxt(NULL);
  if (!ctxt)
    return 0;

  xmlParserInputPtr inputStream = xmlParserInputBufferCreateFd(ctxt, fileno(fp), XML_CHAR_ENCODING_UTF8);
  xmlParserInputPtr externalInputStream = xmlParserInputBufferCreateFd(ctxt, fileno(fp), XML_CHAR_ENCODING_UTF8);
  xmlParserInputPtr errorInputStream = xmlParserInputBufferCreateFd(ctxt, fileno(fp), XML_CHAR_ENCODING_UTF8);

  xmlParserCtxtPtr subctxt = XML_ExternalEntityParserCreate(ctxt, test_file, NULL);

  xmlParseDocument(subctxt, inputStream);
  xmlParseDocument(ctxt, externalInputStream);
  xmlParseDocument(ctxt, errorInputStream);

  xmlFreeParserCtxt(subctxt);
  xmlFreeParserCtxt(ctxt);
  remove(test_file);
  return 0;
}