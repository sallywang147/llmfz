#include "tinyxml2/tinyxml2.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  // Consume some data to use as the XML string.
  std::string xml_string = provider.ConsumeRandomLengthString();

  // Consume some data to use as the default value.
  double default_value = provider.ConsumeFloatingPoint<double>();

  // Parse the XML string.
  XMLDocument doc;
  doc.Parse(xml_string.c_str());

  // Get the root element.
  XMLElement* root = doc.RootElement();

  // If the root element exists, call DoubleText() on it.
  if (root) {
    root->DoubleText(default_value);
  }

  return 0;
}