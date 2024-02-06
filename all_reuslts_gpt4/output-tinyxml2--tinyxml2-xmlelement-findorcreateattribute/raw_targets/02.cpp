#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string name = stream.ConsumeRandomLengthString();
  
  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement* elem = doc.NewElement("Element");
  doc.InsertFirstChild(elem);
  
  elem->FindOrCreateAttribute(name.c_str());

  return 0;
}