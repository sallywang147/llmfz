#include "tinyxml2/tinyxml2.h"
#include <fuzzer/FuzzedDataProvider.h>

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xml_string = stream.ConsumeRemainingBytesAsString();

  XMLDocument doc;
  doc.Parse(xml_string.c_str());

  XMLElement* root = doc.RootElement();
  if (root) {
    XMLElement* cloned = root->ShallowClone(&doc);
    if (cloned) {
      doc.DeleteNode(cloned);
    }
  }

  return 0;
}