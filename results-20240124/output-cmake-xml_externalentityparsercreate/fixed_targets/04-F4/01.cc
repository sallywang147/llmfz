#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  xmlParserCtxtPtr ctxt = xmlCreateFileParserCtxt(test_file);
  xmlParseDocument(ctxt);

  // Call the missing function
  XML_ExternalEntityParserCreate(ctxt, NULL, NULL);

  xmlFreeParserCtxt(ctxt);

  remove(test_file);
  return 0;
}