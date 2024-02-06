#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libxml/tree.h"
#include "libxml/xmlsave.h"
#include "libxml/xmlIO.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file for output
  FILE *output = tmpfile();
  if (output == NULL) {
    return 0;
  }

  // Create a temporary file for input
  FILE *input = tmpfile();
  if (input == NULL) {
    fclose(output);
    return 0;
  }

  // Write data to the input file
  std::string str = stream.ConsumeRemainingBytesAsString();
  fwrite(str.c_str(), 1, str.size(), input);
  rewind(input);

  // Create a dummy xmlDoc
  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");

  xmlShell(doc, (char*)"dummy.xml", input, output);

  // Cleanup
  xmlFreeDoc(doc);
  fclose(input);
  fclose(output);

  return 0;
}