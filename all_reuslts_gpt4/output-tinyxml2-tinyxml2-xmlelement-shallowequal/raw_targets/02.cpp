#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  
  std::string xml1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string xml2 = stream.ConsumeRemainingBytesAsString();
  
  XMLDocument doc1, doc2;
  doc1.Parse(xml1.c_str());
  doc2.Parse(xml2.c_str());

  XMLElement* element1 = doc1.FirstChildElement();
  XMLElement* element2 = doc2.FirstChildElement();
  
  if (element1 && element2) {
    element1->ShallowEqual(element2);
  }
  
  return 0;
}