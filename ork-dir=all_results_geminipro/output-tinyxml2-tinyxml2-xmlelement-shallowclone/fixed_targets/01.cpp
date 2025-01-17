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
extern "C" {
#include <crtdbg.h>
}
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
  XMLElement *root = doc.FirstChildElement();
  if (root == nullptr) {
    return 0;
  }

  XMLElement *clone = root->ShallowClone(&doc);
  if (clone == nullptr) {
    return 0;
  }

  doc.DeleteNode(clone);  // Delete the clone before returning.

  return 0;
}

// Define the missing function.
extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  // Do nothing.
  return 0;
}