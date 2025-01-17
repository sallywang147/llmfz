#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "tinyxml2.h"

extern "C" {
#include "llvm/ADT/ArrayRef.h"
#include "llvm/Fuzz/FuzzedDataProvider.h"
}

using namespace tinyxml2;

static void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  XMLDocument doc;
  std::string xml_string = fuzzed_data.ConsumeRandomLengthString(size);
  doc.Parse(xml_string.c_str());

  XMLPrinter printer;
  doc.Print(&printer);  // Fix: Call Print() to print the XML document.
}