#include <fuzzer/FuzzedDataProvider.h>

#include <libxml/parser.h>
#include <libxml/relaxng.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemavalid.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlSchemaValidCtxtPtr ctxt;
  xmlSchemaParserCtxtPtr pctxt;
  xmlSchemaPtr schema;
  xmlDocPtr doc;
  int ret;

  ctxt = xmlSchemaNewValidCtxt();
  if (ctxt == NULL) {
    return 0;
  }

  pctxt = xmlSchemaNewParserCtxt(ctxt);
  if (pctxt == NULL) {
    xmlSchemaFreeValidCtxt(ctxt);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t schema_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  auto schema_data = provider.ConsumeBytes<char>(schema_size);
  schema = xmlSchemaParseMem(schema_data.data(), schema_data.size(), pctxt);
  xmlSchemaFreeParserCtxt(pctxt);
  if (schema == NULL) {
    xmlSchemaFreeValidCtxt(ctxt);
    return 0;
  }

  const size_t doc_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  auto doc_data = provider.ConsumeBytes<char>(doc_size);
  doc = xmlParseMemory(doc_data.data(), doc_data.size());
  if (doc == NULL) {
    xmlSchemaFree(schema);
    xmlSchemaFreeValidCtxt(ctxt);
    return 0;
  }

  // Call the missing function here.
  ret = xmlSchemaValidateDoc(ctxt, doc);
  if (ret != 0) {
    fprintf(stderr, "Validation failed.\n");
  }

  xmlFreeDoc(doc);
  xmlSchemaFree(schema);
  xmlSchemaFreeValidCtxt(ctxt);
  return 0;
}