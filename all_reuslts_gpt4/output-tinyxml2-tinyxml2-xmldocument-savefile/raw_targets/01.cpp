#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinyxml2::XMLDocument doc;
  const char* filename = "/tmp/fuzz.xml";
  bool compact = stream.ConsumeBool();

  doc.SaveFile(filename, compact);

  return 0;
}