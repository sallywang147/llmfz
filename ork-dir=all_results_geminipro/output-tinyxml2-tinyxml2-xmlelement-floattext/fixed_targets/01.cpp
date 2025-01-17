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

  XMLElement* root = doc.RootElement();
  if (root == nullptr) {
    return 0;
  }

  // Fix: Use SetAttribute() to correctly set a floating-point attribute on the root element.
  root->SetAttribute("value", 0.0f);

  // Fix: Call FloatText() to access the attribute value as a float.
  float value = root->FloatText("value", 0.0f);

  // Use the attribute value in some way.
  if (value > 0.0f) {
    // Do something with the positive value.
  }

  return 0;
}