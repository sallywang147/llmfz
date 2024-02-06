#include "tinyxml2/tinyxml2.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xml_string = stream.ConsumeRemainingBytesAsString();

  XMLDocument doc;
  doc.Parse(xml_string.c_str());

  XMLElement* root = doc.RootElement();
  if (root) {
    uint64_t defaultValue = stream.ConsumeIntegral<uint64_t>();
    uint64_t result = root->Unsigned64Text(defaultValue);
  }

  return 0;
}