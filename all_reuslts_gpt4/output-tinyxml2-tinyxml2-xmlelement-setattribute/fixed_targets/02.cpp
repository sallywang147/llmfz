#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  XMLDocument doc;
  XMLElement *element = doc.NewElement("Element");

  if (stream.remaining_bytes() > 1) {
    std::string name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<uint8_t>(1, stream.remaining_bytes() / 2));
    std::string value = stream.ConsumeRemainingBytesAsString();

    element->SetAttribute(name.c_str(), value.c_str());
  }

  return 0;
}