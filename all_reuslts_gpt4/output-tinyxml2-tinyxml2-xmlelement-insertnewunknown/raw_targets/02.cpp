#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  const char *text = str.c_str();

  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement *elem = doc.NewElement("root");
  doc.InsertFirstChild(elem);

  elem->InsertNewUnknown(text);

  return 0;
}