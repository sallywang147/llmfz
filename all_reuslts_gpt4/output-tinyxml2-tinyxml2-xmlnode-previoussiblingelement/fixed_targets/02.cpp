#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string xml_string = stream.ConsumeRandomLengthString();
  std::string element_name = stream.ConsumeRandomLengthString();

  tinyxml2::XMLDocument doc;
  doc.Parse(xml_string.c_str());

  // Traverse all nodes in the document
  for (tinyxml2::XMLNode* node = doc.FirstChild(); node; node = node->NextSibling()) {
    // Call PreviousSiblingElement on each node
    const tinyxml2::XMLElement* element = node->PreviousSiblingElement(element_name.c_str());
    // Do something with the element to ensure the function call isn't optimized away
    if (element) {
      volatile const char* name = element->Name();
    }
  }

  return 0;
}