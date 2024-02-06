#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "libxml/parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  // Initialize XML parser.
  xmlInitParser();

  // Create a new XML parser.
  xmlParserCtxtPtr ctxt = xmlNewParserCtxt();
  if (ctxt == NULL)
    return 0;

  // Set the input buffer.
  xmlCtxtUseOptions(ctxt, XML_PARSE_NONET);
  xmlCtxtReadMemory(ctxt, data, size, "fuzz");

  // Create a new encoding.
  struct encoding *enc = XmlInitUnknownEncodingNS((char *)data, NULL, NULL, NULL);
  if (enc == NULL)
    return 0;

  // Parse the input.
  xmlParseDocument(ctxt);

  // Clean up.
  xmlFreeParserCtxt(ctxt);
  xmlCleanupParser();
  xmlFreeEncoding(enc);

  return 0;
}