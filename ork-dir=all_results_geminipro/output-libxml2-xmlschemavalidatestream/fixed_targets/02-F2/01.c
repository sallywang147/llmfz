#include <fuzzer/FuzzedDataProvider.h>

#include <libxml/xmlschemas.h>

extern "C" {
#include <stdlib.h>
#include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewParserCtxt(nullptr);
  if (!parser_ctxt) return 0;
  xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(parser_ctxt);
  if (!valid_ctxt) {
    xmlSchemaFreeParserCtxt(parser_ctxt);
    return 0;
  }

  // Use a random encoding.
  int enc = provider.ConsumeIntegralInRange<int>(0, 10);
  // Use a random schema.
  const char *schema_data = provider.ConsumeRemainingBytesAsString().c_str();
  xmlSchemaPtr schema = xmlSchemaParseMemory(schema_data, strlen(schema_data));
  if (!schema) {
    xmlSchemaFreeValidCtxt(valid_ctxt);
    xmlSchemaFreeParserCtxt(parser_ctxt);
    return 0;
  }
  xmlSchemaSetValidCtxt(valid_ctxt, schema);

  // Use a random SAX handler.
  xmlSAXHandler *sax = xmlSAXNewDefaultHandler();
  if (!sax) {
    xmlSchemaFree(schema);
    xmlSchemaFreeValidCtxt(valid_ctxt);
    xmlSchemaFreeParserCtxt(parser_ctxt);
    return 0;
  }
  xmlSchemaSetSAXHandler(valid_ctxt, sax);

  // Use a random input buffer.
  xmlParserInputBufferPtr input = xmlParserInputBufferCreateMem(
      provider.ConsumeRemainingBytes().data(), provider.remaining_bytes(), enc);
  if (!input) {
    xmlSAXFreeHandler(sax);
    xmlSchemaFree(schema);
    xmlSchemaFreeValidCtxt(valid_ctxt);
    xmlSchemaFreeParserCtxt(parser_ctxt);
    return 0;
  }

  // Validate the input.
  int ret = xmlSchemaValidateStream(valid_ctxt, input, enc, sax, nullptr);

  // Cleanup.
  xmlParserInputBufferFree(input);
  xmlSAXFreeHandler(sax);
  xmlSchemaFree(schema);
  xmlSchemaFreeValidCtxt(valid_ctxt);
  xmlSchemaFreeParserCtxt(parser_ctxt);

  return ret;
}