#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/xmlschemas.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlInitParser();
  FuzzedDataProvider stream(data, size);

  // Create a parser context
  xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewParserCtxt("http://www.w3.org/2001/XMLSchema");
  if (parser_ctxt == NULL) {
    xmlCleanupParser();
    return 0;
  }

  // Parse the schema
  xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
  if (schema == NULL) {
    xmlSchemaFreeParserCtxt(parser_ctxt);
    xmlCleanupParser();
    return 0;
  }

  // Create a validation context
  xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);
  if (valid_ctxt == NULL) {
    xmlSchemaFree(schema);
    xmlSchemaFreeParserCtxt(parser_ctxt);
    xmlCleanupParser();
    return 0;
  }

  // Create an input buffer
  xmlParserInputBufferPtr input = xmlParserInputBufferCreateMem((char*)data, size, XML_CHAR_ENCODING_NONE);
  if (input == NULL) {
    xmlSchemaFreeValidCtxt(valid_ctxt);
    xmlSchemaFree(schema);
    xmlSchemaFreeParserCtxt(parser_ctxt);
    xmlCleanupParser();
    return 0;
  }

  // Create a SAX handler
  xmlSAXHandlerPtr sax = (xmlSAXHandlerPtr) malloc(sizeof(xmlSAXHandler));
  memset(sax, 0, sizeof(xmlSAXHandler));

  // Validate the stream
  int user_data_size = stream.remaining_bytes();
  std::string user_data = stream.ConsumeBytesAsString(user_data_size);
  int ret = xmlSchemaValidateStream(valid_ctxt, input, XML_CHAR_ENCODING_NONE, sax, (void *)user_data.c_str());

  // Cleanup
  xmlFree(sax);
  xmlFreeParserInputBuffer(input);
  xmlSchemaFreeValidCtxt(valid_ctxt);
  xmlSchemaFree(schema);
  xmlSchemaFreeParserCtxt(parser_ctxt);
  xmlCleanupParser();

  return 0;
}