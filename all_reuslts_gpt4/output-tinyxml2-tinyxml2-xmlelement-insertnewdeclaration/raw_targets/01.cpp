#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  XMLDocument doc;
  XMLElement* root = doc.NewElement("Root");
  doc.InsertFirstChild(root);

  std::string str = stream.ConsumeRemainingBytesAsString();
  root->InsertNewDeclaration(str.c_str());

  return 0;
}