#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;
using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string data_string(reinterpret_cast<const char *>(data), size);
  XMLDocument doc;
  doc.Parse(data_string.c_str());

  // Get the root element
  XMLElement* root = doc.RootElement();
  if (root != nullptr) {
    // Call GetText() on the root element
    const char* text = root->GetText();
  }

  return 0;
}