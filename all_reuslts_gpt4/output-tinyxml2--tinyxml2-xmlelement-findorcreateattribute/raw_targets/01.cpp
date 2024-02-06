#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string attr_name = stream.ConsumeRandomLengthString();
  XMLDocument doc;
  XMLElement* root = doc.NewElement("Root");
  doc.InsertFirstChild(root);
  root->FindOrCreateAttribute(attr_name.c_str());
  return 0;
}