#include <fuzzer/FuzzedDataProvider.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlschemas.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Initialize libxml2.
  xmlInitParser();
  LIBXML_TEST_VERSION

  // Create a FuzzedDataProvider instance.
  FuzzedDataProvider fuzzed_data(data, size);

  // Create a reader from the fuzzed data.
  xmlTextReaderPtr reader = xmlReaderForMemory(reinterpret_cast<const char*>(data), size, NULL, NULL, 0);
  if (reader == NULL) {
    // Failed to create a reader.
    xmlCleanupParser();
    return 0;
  }

  // Create a schema validation context.
  xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(NULL);
  if (ctxt == NULL) {
    // Failed to create a schema validation context.
    xmlFreeTextReader(reader);
    xmlCleanupParser();
    return 0;
  }

  // Get an integer for the options.
  int options = fuzzed_data.ConsumeIntegral<int>();

  // Call the target function.
  xmlTextReaderSchemaValidateCtxt(reader, ctxt, options);

  // Cleanup.
  xmlSchemaFreeValidCtxt(ctxt);
  xmlFreeTextReader(reader);
  xmlCleanupParser();

  return 0;
}