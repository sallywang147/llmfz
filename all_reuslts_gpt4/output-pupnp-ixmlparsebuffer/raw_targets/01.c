#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ixml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string buffer = stream.ConsumeRemainingBytesAsString();

  struct _IXML_Document *doc = ixmlParseBuffer(const_cast<char*>(buffer.c_str()));
  if (doc) {
    ixmlDocument_free(doc);
  }

  return 0;
}