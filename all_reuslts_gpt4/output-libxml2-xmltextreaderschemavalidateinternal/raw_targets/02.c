#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/xmlreader.h"
#include "libxml/xmlschemas.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create a reader context
  xmlTextReaderPtr reader = xmlReaderForMemory(reinterpret_cast<const char*>(data), size, "", NULL, 0);
  if (!reader) {
    return 0;
  }

  // Create a schema validation context
  xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(NULL);
  if (!ctxt) {
    xmlFreeTextReader(reader);
    return 0;
  }

  // Consume some data for the xsd
  std::string xsd = provider.ConsumeBytesAsString(provider.remaining_bytes() / 2);
  
  // Consume some data for the options
  int options = provider.ConsumeIntegral<int>();

  // Call the function under test
  xmlTextReaderSchemaValidateInternal(reader, const_cast<char*>(xsd.c_str()), ctxt, options);

  // Clean up
  xmlSchemaFreeValidCtxt(ctxt);
  xmlFreeTextReader(reader);

  return 0;
}