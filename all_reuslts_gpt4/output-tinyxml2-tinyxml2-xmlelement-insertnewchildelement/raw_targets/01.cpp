#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create an XMLDocument and an XMLElement to work with
  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement *elem = doc.NewElement("Root");

  // Initialize the data provider for fuzzing
  FuzzedDataProvider stream(data, size);

  // Consume the data as a string to use as the name parameter
  std::string name = stream.ConsumeRemainingBytesAsString();

  // Call the function to be fuzzed
  elem->InsertNewChildElement(name.c_str());

  return 0;
}