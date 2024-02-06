#if defined(_MSC_VER)
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

extern "C" {
#include "tinyxml2/tinyxml2.h"
}

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

  FuzzedDataProvider stream(data, size);
  const std::string name = stream.ConsumeRemainingBytesAsString();
  const std::string value = stream.ConsumeRemainingBytesAsString();

  // Fix: Check if the attribute already exists before setting it.
  if (root->Attribute(name.c_str()) == nullptr) {
    root->SetAttribute(name.c_str(), value.c_str());
  }

  return 0;
}