#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2/tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  
  tinyxml2::XMLDocument doc;
  doc.Parse(str.c_str());
  
  // Traverse through all elements and call Unsigned64Text on each
  for (tinyxml2::XMLElement* elem = doc.FirstChildElement(); elem; elem = elem->NextSiblingElement()) {
    uint64_t defaultValue = stream.ConsumeIntegral<uint64_t>();
    elem->Unsigned64Text(defaultValue);
  }

  return 0;
}