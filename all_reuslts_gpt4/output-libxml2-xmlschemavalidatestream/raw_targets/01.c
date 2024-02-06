#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/xmlschemas.h"
#include "libxml/parser.h"
#include "libxml/parserInternals.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Prepare the input buffer
  xmlParserInputBufferPtr input = xmlAllocParserInputBuffer(XML_CHAR_ENCODING_NONE);
  if (input == NULL) {
    return 0;
  }
  input->buffer->use = stream.ConsumeIntegralInRange<int>(0, size);
  input->buffer->size = stream.ConsumeIntegralInRange<int>(0, size);
  auto buffer_data = stream.ConsumeRemainingBytes<unsigned char>();
  memcpy(input->buffer->content, buffer_data.data(), buffer_data.size());

  // Prepare the validation context
  xmlSchemaParserCtxtPtr pctxt = xmlSchemaNewParserCtxt(NULL);
  xmlSchemaPtr schema = xmlSchemaParse(pctxt);
  xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(schema);

  // Prepare the SAX handler
  xmlSAXHandlerPtr sax = (xmlSAXHandlerPtr) xmlMalloc(sizeof(xmlSAXHandler));
  memset(sax, 0, sizeof(xmlSAXHandler));

  // Prepare user data
  std::string user_data = stream.ConsumeRandomLengthString();
  char* user_data_ptr = (char*) user_data.c_str();

  // Call the function to fuzz
  xmlSchemaValidateStream(ctxt, input, XML_CHAR_ENCODING_NONE, sax, user_data_ptr);

  // Cleanup
  xmlFree(sax);
  xmlSchemaFreeValidCtxt(ctxt);
  xmlSchemaFree(schema);
  xmlSchemaFreeParserCtxt(pctxt);
  xmlFreeParserInputBuffer(input);

  return 0;
}