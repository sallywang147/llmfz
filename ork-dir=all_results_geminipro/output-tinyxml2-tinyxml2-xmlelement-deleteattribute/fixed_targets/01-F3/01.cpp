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

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string data_string(reinterpret_cast<const char *>(data), size);
  XMLDocument doc;
  doc.Parse(data_string.c_str());

  XMLElement* element = doc.FirstChildElement();
  if (!element) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  while (element) {
    const char* attribute_name = provider.ConsumeRandomLengthString().c_str();
    if (element->DeleteAttribute(attribute_name)) {
      // Attribute was found and deleted.
    } else {
      // Attribute was not found. Move on to the next element.
      element = element->NextSiblingElement();
      continue;
    }
    element = element->NextSiblingElement();
  }

  return 0;
}