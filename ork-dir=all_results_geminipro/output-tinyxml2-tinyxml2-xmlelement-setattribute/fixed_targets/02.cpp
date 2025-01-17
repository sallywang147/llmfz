#if defined(_MSC_VER)
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS 
#endif
#endif
#include "tinyxml2/tinyxml2.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

#if defined(_MSC_VER) || defined(WIN32)
#include <crtdbg.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
_CrtMemState startMemState;
_CrtMemState endMemState;
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

using namespace tinyxml2;
using namespace std;

extern "C" {
// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string data_string(reinterpret_cast<const char *>(data), size);
  XMLDocument doc;
  doc.Parse(data_string.c_str());

  XMLElement *root = doc.FirstChildElement();
  if (root == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t max_attr_name_len = 100;
  const size_t max_attr_value_len = 100;
  const size_t max_attrs = 10;

  for (size_t i = 0; i < max_attrs; i++) {
    std::string attr_name = provider.ConsumeBytesAsString(
        provider.ConsumeIntegralInRange<size_t>(1, max_attr_name_len));
    std::string attr_value = provider.ConsumeBytesAsString(
        provider.ConsumeIntegralInRange<size_t>(1, max_attr_value_len));
    root->SetAttribute(attr_name.c_str(), attr_value.c_str());
  }

  return 0;
}
}