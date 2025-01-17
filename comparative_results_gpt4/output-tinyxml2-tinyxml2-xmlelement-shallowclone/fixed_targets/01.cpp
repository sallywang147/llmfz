#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  tinyxml2::XMLDocument doc;
  std::string xml(reinterpret_cast<const char *>(data), size);
  doc.Parse(xml.c_str());

  tinyxml2::XMLElement* root = doc.RootElement();
  if (root) {
    tinyxml2::XMLNode* clone = root->ShallowClone(&doc);
    if (clone) {
      // Do something with the clone, e.g. add it to the document.
      doc.InsertEndChild(clone);
    }
  }

  return 0;
}