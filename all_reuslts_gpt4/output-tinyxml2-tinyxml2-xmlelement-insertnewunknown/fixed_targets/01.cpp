#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();

  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement* element = doc.NewElement("Element");
  doc.InsertFirstChild(element);

  element->InsertNewUnknown(str.c_str());

  return 0;
}