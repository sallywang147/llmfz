#include <fuzzer/FuzzedDataProvider.h>

#include <libxml/parser.h>
#include <libxml/relaxng.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschema.h>

extern "C" {
#include <stdlib.h>
#include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlRelaxNGParserCtxtPtr rng_ctxt;
  xmlRelaxNGPtr rng;
  xmlSchemaParserCtxtPtr schema_ctxt;
  xmlSchemaPtr schema;
  xmlSchemaValidCtxtPtr valid_ctxt;
  int ret;

  rng_ctxt = xmlRelaxNGNewParserCtxt();
  if (rng_ctxt == NULL) {
    return 0;
  }

  rng = xmlRelaxNGParse(rng_ctxt, "test.rng");
  if (rng == NULL) {
    xmlRelaxNGFreeParserCtxt(rng_ctxt);
    return 0;
  }

  schema_ctxt = xmlSchemaNewParserCtxt("test.xsd");
  if (schema_ctxt == NULL) {
    xmlRelaxNGFree(rng);
    xmlRelaxNGFreeParserCtxt(rng_ctxt);
    return 0;
  }

  schema = xmlSchemaParse(schema_ctxt);
  if (schema == NULL) {
    xmlSchemaFreeParserCtxt(schema_ctxt);
    xmlRelaxNGFree(rng);
    xmlRelaxNGFreeParserCtxt(rng_ctxt);
    return 0;
  }

  valid_ctxt = xmlSchemaNewValidCtxt(schema);
  if (valid_ctxt == NULL) {
    xmlSchemaFree(schema);
    xmlSchemaFreeParserCtxt(schema_ctxt);
    xmlRelaxNGFree(rng);
    xmlRelaxNGFreeParserCtxt(rng_ctxt);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string filename = provider.ConsumeRandomLengthString(1024);

  ret = xmlSchemaValidateFile(valid_ctxt, filename.c_str(), 0);
  if (ret != 0) {
    xmlSchemaFreeValidCtxt(valid_ctxt);
    xmlSchemaFree(schema);
    xmlSchemaFreeParserCtxt(schema_ctxt);
    xmlRelaxNGFree(rng);
    xmlRelaxNGFreeParserCtxt(rng_ctxt);
    return 0;
  }

  xmlSchemaFreeValidCtxt(valid_ctxt);
  xmlSchemaFree(schema);
  xmlSchemaFreeParserCtxt(schema_ctxt);
  xmlRelaxNGFree(rng);
  xmlRelaxNGFreeParserCtxt(rng_ctxt);

  return 0;
}