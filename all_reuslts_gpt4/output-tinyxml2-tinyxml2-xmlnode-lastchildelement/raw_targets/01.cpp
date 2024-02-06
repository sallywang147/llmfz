#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string xmlData = stream.ConsumeRandomLengthString();
  std::string name = stream.ConsumeRemainingBytesAsString();

  tinyxml2::XMLDocument doc;
  doc.Parse(xmlData.c_str());

  doc.LastChildElement(name.c_str());

  return 0;
}