#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new XML document
  XMLDocument doc;
  
  // Create a new element
  XMLElement* element = doc.NewElement("Element");

  // Add some attributes to the element
  element->SetAttribute("attr1", "value1");
  element->SetAttribute("attr2", "value2");
  element->SetAttribute("attr3", "value3");

  // Add the element to the document
  doc.InsertFirstChild(element);

  // Consume the remaining bytes as a string
  std::string attrName = stream.ConsumeRemainingBytesAsString();

  // Delete the attribute
  element->DeleteAttribute(attrName.c_str());

  return 0;
}