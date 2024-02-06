#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Split the input data into two parts: xml_string and name.
  const std::string xml_string = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  const std::string name = stream.ConsumeRemainingBytesAsString();

  XMLDocument doc;
  doc.Parse(xml_string.c_str());

  // Iterate over all nodes in the document.
  for (const XMLNode* node = doc.FirstChild(); node != nullptr; node = node->NextSibling()) {
    // Call the function to fuzz.
    const XMLElement* element = node->PreviousSiblingElement(name.c_str());
  }

  return 0;
}