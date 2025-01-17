#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/xmlreader.h"
#include "libxml/xmlschemas.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    xmlInitParser();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Split the input data into two parts: one for the reader and one for the schema
  const size_t reader_data_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string reader_data = stream.ConsumeBytesAsString(reader_data_size);
  std::string xsd = stream.ConsumeRemainingBytesAsString();

  // Create the reader from the first part of the data
  xmlTextReaderPtr reader = xmlReaderForMemory(reader_data.data(), reader_data.size(), NULL, NULL, 0);
  if (!reader) {
    return 0;
  }

  // Create the schema from the second part of the data
  xmlDocPtr schema_doc = xmlReadMemory(xsd.data(), xsd.size(), NULL, NULL, 0);
  if (!schema_doc) {
    xmlFreeTextReader(reader);
    return 0;
  }

  xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewDocParserCtxt(schema_doc);
  if (!parser_ctxt) {
    xmlFreeDoc(schema_doc);
    xmlFreeTextReader(reader);
    return 0;
  }

  xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
  xmlSchemaFreeParserCtxt(parser_ctxt);
  if (!schema) {
    xmlFreeDoc(schema_doc);
    xmlFreeTextReader(reader);
    return 0;
  }

  xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);
  if (!valid_ctxt) {
    xmlSchemaFree(schema);
    xmlFreeDoc(schema_doc);
    xmlFreeTextReader(reader);
    return 0;
  }

  // Consume an integer from the remaining data for the options parameter
  int options = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  xmlTextReaderSchemaValidateInternal(reader, xsd.data(), valid_ctxt, options);

  // Clean up
  xmlSchemaFreeValidCtxt(valid_ctxt);
  xmlSchemaFree(schema);
  xmlFreeDoc(schema_doc);
  xmlFreeTextReader(reader);

  return 0;
}