#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xml_string = stream.ConsumeRemainingBytesAsString();

  // Parse the XML document from the fuzzed data
  XMLDocument doc;
  doc.Parse(xml_string.c_str());

  // Create an XMLPrinter and print the document to it
  XMLPrinter printer;
  doc.Print(&printer);

  return 0;
}