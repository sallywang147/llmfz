#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/xmlschemas.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize libxml2.
  xmlInitParser();

  // Create a validation context.
  xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(NULL);
  if (ctxt == NULL) {
    xmlCleanupParser();
    return 0;
  }

  // Create a temporary file with the input data.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    xmlSchemaFreeValidCtxt(ctxt);
    xmlCleanupParser();
    return 0;
  }

  // Write data to the file.
  size_t written = write(fd, data, size);
  close(fd);
  if (written != size) {
    unlink(filename);
    xmlSchemaFreeValidCtxt(ctxt);
    xmlCleanupParser();
    return 0;
  }

  // Extract options from the data.
  int options = stream.ConsumeIntegral<int>();

  // Validate the file.
  xmlSchemaValidateFile(ctxt, filename, options);

  // Clean up.
  unlink(filename);
  xmlSchemaFreeValidCtxt(ctxt);
  xmlCleanupParser();

  return 0;
}