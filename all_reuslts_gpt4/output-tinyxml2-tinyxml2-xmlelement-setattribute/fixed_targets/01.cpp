#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"
#include <cstddef>
#include <cstdint>
#include <string>

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a new XMLDocument and XMLElement
  XMLDocument doc;
  XMLElement* elem = doc.NewElement("Element");

  // Consume data for name and value
  std::string name = stream.ConsumeRandomLengthString();
  std::string value = stream.ConsumeRemainingBytesAsString();

  // Set the attribute
  elem->SetAttribute(name.c_str(), value.c_str());

  // Add the element to the document
  doc.InsertFirstChild(elem);

  return 0;
}