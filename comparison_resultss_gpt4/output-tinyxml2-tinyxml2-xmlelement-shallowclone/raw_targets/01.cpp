#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement* elem = doc.NewElement("TestElement");

  // Shallow clone the element
  tinyxml2::XMLNode* clonedElem = elem->ShallowClone(&doc);

  return 0;
}