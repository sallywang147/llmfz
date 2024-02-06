#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  tinyxml2::XMLDocument doc;

  // Create a root element to insert a new child element into
  tinyxml2::XMLElement* root = doc.NewElement("root");
  doc.InsertFirstChild(root);

  // Extract a string to use as the name of the new child element
  std::string name = stream.ConsumeRandomLengthString();
  root->InsertNewChildElement(name.c_str());

  return 0;
}