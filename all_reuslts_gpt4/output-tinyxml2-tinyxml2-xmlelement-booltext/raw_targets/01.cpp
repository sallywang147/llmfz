#include "tinyxml2/tinyxml2.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  tinyxml2::XMLDocument doc;
  std::string xml_data = fuzzed_data.ConsumeRemainingBytesAsString();
  doc.Parse(xml_data.c_str());

  tinyxml2::XMLElement* root = doc.RootElement();
  if (root) {
    bool default_value = fuzzed_data.ConsumeBool();
    root->BoolText(default_value);
  }

  return 0;
}