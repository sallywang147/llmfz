#include "tinyxml2/tinyxml2.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string>

using namespace tinyxml2;
using namespace std;

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string data_string(reinterpret_cast<const char *>(data), size);
  XMLDocument doc;
  doc.Parse(data_string.c_str());

  XMLDocument target;
  doc.DeepCopy(&target);

  return 0;
}