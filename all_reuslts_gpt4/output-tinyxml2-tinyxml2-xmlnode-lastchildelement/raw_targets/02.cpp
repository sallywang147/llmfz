#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"
#include <cstddef>
#include <cstdint>
#include <string>

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xml_string = stream.ConsumeRandomLengthString();
  std::string element_name = stream.ConsumeRemainingBytesAsString();

  XMLDocument doc;
  doc.Parse(xml_string.c_str());

  // Call the function to fuzz
  doc.LastChildElement(element_name.c_str());

  return 0;
}