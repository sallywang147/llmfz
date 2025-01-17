#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;
using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string data_string = stream.ConsumeRemainingBytesAsString();
  XMLDocument doc;
  doc.Parse(data_string.c_str());

  XMLElement* root = doc.RootElement();
  if (root) {
    float defaultValue = stream.ConsumeFloatingPoint<float>();
    root->FloatText(defaultValue);
  }

  return 0;
}