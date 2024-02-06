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

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string data_string(reinterpret_cast<const char *>(data), size);
  XMLDocument doc;
  doc.Parse(data_string.c_str());

  const XMLElement* root = doc.FirstChildElement();
  if (root == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const std::string name = provider.ConsumeRandomLengthString();

  // Fix: Check if the element exists before accessing its children.
  if (root->FirstChildElement(name.c_str()) == nullptr) {
    return 0;
  }
  const XMLElement* element = root->FirstChildElement(name.c_str());

  // Fix: Check if the last element exists before accessing its children.
  if (root->LastChildElement(name.c_str()) == nullptr) {
    return 0;
  }
  const XMLElement* last_element = root->LastChildElement(name.c_str());

  return 0;
}