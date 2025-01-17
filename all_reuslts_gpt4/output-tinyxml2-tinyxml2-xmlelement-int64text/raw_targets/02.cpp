#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2/tinyxml2.h>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xml_string = stream.ConsumeRemainingBytesAsString();
  
  tinyxml2::XMLDocument doc;
  doc.Parse(xml_string.c_str());
  
  // Get the root element
  tinyxml2::XMLElement* root = doc.RootElement();
  
  // If root is null, the XML document is empty or invalid
  if (root == nullptr) {
    return 0;
  }

  // Get a default value from the fuzzer
  int64_t default_value = stream.ConsumeIntegral<int64_t>();

  // Call the target function
  root->Int64Text(default_value);

  return 0;
}