#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/xmlschemas.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlSchemaParserCtxtPtr ctxt;
  xmlSchemaPtr schema = NULL;
  xmlSchemaValidCtxtPtr vctxt = NULL;
  int ret;

  if (xmlSchemaInitTypes() != 0) {
    fprintf(stderr, "Could not initialize schema types\n");
    return 0;
  }

  ctxt = xmlSchemaNewParserCtxt("file.xsd");
  if (ctxt == NULL) {
    fprintf(stderr, "Could not create XSD schema parsing context\n");
    return 0;
  }

  schema = xmlSchemaParse(ctxt);
  xmlSchemaFreeParserCtxt(ctxt);
  if (schema == NULL) {
    fprintf(stderr, "Could not parse XSD schema\n");
    return 0;
  }

  vctxt = xmlSchemaNewValidCtxt(schema);
  if (vctxt == NULL) {
    fprintf(stderr, "Could not create XSD schema validation context\n");
    xmlSchemaFree(schema);
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Extract a string to use as filename
  std::string filename = provider.ConsumeRandomLengthString();
  // Extract an integer to use as options
  int options = provider.ConsumeIntegral<int>();

  ret = xmlSchemaValidateFile(vctxt, const_cast<char*>(filename.c_str()), options);

  xmlSchemaFreeValidCtxt(vctxt);
  xmlSchemaFree(schema);
  xmlSchemaCleanupTypes();

  return 0;
}