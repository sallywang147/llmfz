#include "tinyxml2/tinyxml2.h"
#include <fuzzer/FuzzedDataProvider.h>

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string data_string(reinterpret_cast<const char *>(data), size);
  XMLDocument doc;
  doc.Parse(data_string.c_str());

  XMLPrinter printer;
  doc.Print(&printer);

  return 0;
}