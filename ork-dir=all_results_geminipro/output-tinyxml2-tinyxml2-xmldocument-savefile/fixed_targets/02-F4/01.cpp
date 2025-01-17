#if defined(_MSC_VER)
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#if defined(_MSC_VER) || defined(WIN32)
extern "C" {
#include <crtdbg.h>
#include <windows.h>
}
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include "tinyxml2/tinyxml2.h"
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
  FuzzedDataProvider provider(data, size);
  const std::string filename = provider.ConsumeRandomLengthString();
  const bool compact = provider.ConsumeBool();
  doc.SaveFile(filename.c_str(), compact);

  return 0;
}