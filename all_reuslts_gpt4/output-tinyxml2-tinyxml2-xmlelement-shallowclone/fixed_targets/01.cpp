#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xml_data = stream.ConsumeRemainingBytesAsString();

  XMLDocument doc;
  doc.Parse(xml_data.c_str());

  XMLElement* element = doc.FirstChildElement();
  if (element != nullptr) {
    XMLNode* cloned_node = element->ShallowClone(&doc);
    if (cloned_node != nullptr) {
      delete cloned_node;
    }
  }

  return 0;
}