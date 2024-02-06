#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *text = const_cast<char*>(str.c_str());

  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement *root = doc.NewElement("Root");
  doc.InsertFirstChild(root);

  root->InsertNewText(text);

  return 0;
}