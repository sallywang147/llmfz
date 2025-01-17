#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;
using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  XMLDocument doc;
  XMLElement* element = doc.NewElement("Element");
  doc.InsertFirstChild(element);

  // Add a dummy attribute to the element
  element->SetAttribute("Attribute", "Value");

  // Consume the data as a string to use as the attribute name
  string attributeName = stream.ConsumeRemainingBytesAsString();

  // Call the function under test
  element->DeleteAttribute(attributeName.c_str());

  return 0;
}