 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

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

  xmlParseExternalEntity(ctxt, test_file, NULL, NULL);

  xmlFreeParserCtxt(ctxt);
  remove(test_file);
  return 0;
}