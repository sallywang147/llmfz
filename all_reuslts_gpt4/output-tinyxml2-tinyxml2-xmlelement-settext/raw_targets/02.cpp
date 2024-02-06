#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *ptr = const_cast<char*>(str.c_str());

  XMLDocument doc;
  XMLElement* elem = doc.NewElement("TestElement");
  elem->SetText(ptr);

  return 0;
}