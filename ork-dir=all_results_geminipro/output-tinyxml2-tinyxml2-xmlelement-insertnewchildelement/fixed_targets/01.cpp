#if defined(_MSC_VER)
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif
#include "tinyxml2.h"
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

  // Find the first child element.
  XMLElement* first_child = doc.FirstChildElement();
  if (first_child == nullptr) {
    return 0;
  }

  // Insert a new child element with a random name.
  FuzzedDataProvider provider(data, size);
  std::string child_name = provider.ConsumeRandomLengthString();
  XMLElement* new_child = first_child->InsertNewChildElement(child_name.c_str());

  return 0;
}
}