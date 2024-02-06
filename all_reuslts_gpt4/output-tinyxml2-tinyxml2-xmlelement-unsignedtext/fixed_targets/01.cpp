#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Parse XML from the fuzzer input
  XMLDocument doc;
  doc.Parse(reinterpret_cast<const char *>(data), size);
  
  // Get the root element
  XMLElement *root = doc.RootElement();
  if(root == nullptr) {
    return 0;
  }

  // Get a default value from the fuzzer input
  unsigned defaultValue = stream.ConsumeIntegral<unsigned>();
  
  // Call the function to fuzz
  root->UnsignedText(defaultValue);

  return 0;
}