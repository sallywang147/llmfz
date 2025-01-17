#include <fuzzer/FuzzedDataProvider.h>

#include <libxml/parser.h>
#include <libxml/relaxng.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlSchemaValidCtxtPtr ctxt;
  xmlParserInputBufferPtr input;
  int enc;
  xmlSAXHandlerPtr sax;
  char *user_data;

  ctxt = xmlSchemaNewValidCtxt(NULL);
  input = xmlParserInputBufferCreateMem(data, size, XML_CHAR_ENCODING_UTF8);
  enc = XML_CHAR_ENCODING_UTF8;
  sax = xmlSAXNewDefaultHandler();
  user_data = NULL;

  xmlSchemaValidateStream(ctxt, input, enc, sax, user_data);

  xmlSchemaFreeValidCtxt(ctxt);
  xmlFreeParserInputBuffer(input);
  xmlFreeSAXHandler(sax);

  return 0;
}