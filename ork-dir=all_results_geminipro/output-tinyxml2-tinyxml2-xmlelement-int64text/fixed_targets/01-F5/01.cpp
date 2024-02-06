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

  XMLElement* root = doc.FirstChildElement();
  if (root == nullptr) {
    return 0;
  }

  // Fix: Check if the root element has a value before calling Int64Text().
  if (root->Value() == nullptr) {
    return 0;
  }

  // Fix: Add a check for the return value of Int64Text() to handle errors.
  int64_t result;
  if (root->Int64Text(&result) != XML_SUCCESS) {
    return 0;
  }

  return 0;
}