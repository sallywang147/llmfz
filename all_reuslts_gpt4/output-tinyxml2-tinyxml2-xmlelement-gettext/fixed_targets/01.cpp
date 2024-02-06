#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2/tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string xmlData = stream.ConsumeRemainingBytesAsString();
  tinyxml2::XMLDocument doc;
  doc.Parse(xmlData.c_str());

  // Get the root element and call GetText() on it
  tinyxml2::XMLElement *root = doc.RootElement();
  if (root) {
    const char* text = root->GetText();
  }

  return 0;
}