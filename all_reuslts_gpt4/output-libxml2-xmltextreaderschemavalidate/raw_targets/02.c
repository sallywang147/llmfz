#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "libxml/xmlreader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  // Create a new xmlTextReader
  xmlTextReaderPtr reader = xmlReaderForMemory(reinterpret_cast<const char*>(data), size, NULL, NULL, 0);
  if (!reader) {
    return 0;
  }

  // Get the xsd string
  std::string xsd = stream.ConsumeRemainingBytesAsString();
  
  // Call the function to fuzz
  xmlTextReaderSchemaValidate(reader, const_cast<char*>(xsd.c_str()));

  // Clean up
  xmlFreeTextReader(reader);
  
  return 0;
}