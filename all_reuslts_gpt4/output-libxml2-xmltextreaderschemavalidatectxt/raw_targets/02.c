#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/xmlreader.h"
#include "libxml/xmlschemas.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize libxml2.
  xmlInitParser();
  LIBXML_TEST_VERSION

  // Create a reader.
  xmlTextReaderPtr reader = xmlReaderForMemory(reinterpret_cast<const char*>(data), size, nullptr, nullptr, 0);
  if (reader == nullptr) {
    xmlCleanupParser();
    return 0;
  }

  // Create a schema validation context.
  xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(nullptr);
  if (ctxt == nullptr) {
    xmlFreeTextReader(reader);
    xmlCleanupParser();
    return 0;
  }

  // Consume the options from the data provider.
  int options = stream.ConsumeIntegral<int>();

  // Call the function to fuzz.
  xmlTextReaderSchemaValidateCtxt(reader, ctxt, options);

  // Cleanup.
  xmlSchemaFreeValidCtxt(ctxt);
  xmlFreeTextReader(reader);
  xmlCleanupParser();

  return 0;
}