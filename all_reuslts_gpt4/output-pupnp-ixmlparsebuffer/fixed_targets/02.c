#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ixml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ixml_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  std::string str = provider.ConsumeRemainingBytesAsString();
  char *buffer = const_cast<char*>(str.c_str());

  struct _IXML_Document *doc = ixmlParseBuffer(buffer);

  if (doc != nullptr) {
    ixmlDocument_free(doc);
  }

  return 0;
}