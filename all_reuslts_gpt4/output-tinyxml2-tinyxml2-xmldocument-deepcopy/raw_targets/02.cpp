#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tinyxml2::XMLDocument sourceDoc;
  tinyxml2::XMLDocument targetDoc;

  // Parse the input data with the source document
  if (sourceDoc.Parse(reinterpret_cast<const char *>(data), size) != tinyxml2::XML_SUCCESS)
    return 0;

  // Perform deep copy from source document to target document
  sourceDoc.DeepCopy(&targetDoc);

  return 0;
}