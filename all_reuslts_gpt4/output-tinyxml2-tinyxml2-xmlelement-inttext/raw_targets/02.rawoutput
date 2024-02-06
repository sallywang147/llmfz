#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Parse XML document
  XMLDocument doc;
  doc.Parse(reinterpret_cast<const char *>(data), size);
  
  // Get the root element
  XMLElement* root = doc.RootElement();
  
  // If root is null, the document is empty or invalid
  if(root == nullptr)
    return 0;
  
  // Get default value from the stream
  int defaultValue = stream.ConsumeIntegral<int>();
  
  // Call the function
  int result = root->IntText(defaultValue);
  
  return 0;
}