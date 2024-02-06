#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <tinyxml2.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string xml_string = provider.ConsumeRandomLengthString(size);
  tinyxml2::XMLDocument doc;
  doc.Parse(xml_string.c_str());
  doc.SaveFile("output.xml", true);
  return 0;
}