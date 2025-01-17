#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a double value
  double default_value = stream.ConsumeFloatingPoint<double>();

  // Create a XML document and parse the input data
  XMLDocument doc;
  doc.Parse(reinterpret_cast<const char *>(data), size);

  // Get the root element
  XMLElement* root = doc.RootElement();
  if (root != nullptr) {
    // Call the target function
    double value = root->DoubleText(default_value);
  }

  return 0;
}