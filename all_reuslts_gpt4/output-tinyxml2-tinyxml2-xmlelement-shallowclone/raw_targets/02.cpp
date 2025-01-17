#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new XMLDocument
  XMLDocument doc;

  // Create a new XMLElement and add it to the document
  XMLElement* original = doc.NewElement("OriginalElement");
  doc.InsertFirstChild(original);

  // Clone the element using the function to be tested
  XMLElement* clone = original->ShallowClone(&doc);

  // Check if cloning was successful
  if (clone == nullptr) {
    return 0;
  }

  // Add the cloned element to the document
  doc.InsertEndChild(clone);

  return 0;
}