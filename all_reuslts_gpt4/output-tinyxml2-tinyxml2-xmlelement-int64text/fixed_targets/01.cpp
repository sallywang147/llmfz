#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tinyxml2::XMLDocument doc;
  FuzzedDataProvider stream(data, size);
  std::string xml_string = stream.ConsumeRemainingBytesAsString();
  doc.Parse(xml_string.c_str());

  tinyxml2::XMLElement* root = doc.RootElement();
  if (root == nullptr) {
    return 0;
  }

  int64_t defaultValue = stream.ConsumeIntegral<int64_t>();
  root->Int64Text(defaultValue);

  return 0;
}