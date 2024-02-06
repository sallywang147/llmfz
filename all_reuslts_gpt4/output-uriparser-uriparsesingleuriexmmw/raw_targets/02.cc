#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "uriparser/Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  UriUriStructW uri;
  int afterLast = 0;
  int charsRequired = 0;
  int * firstSyntaxErrorPos = nullptr;
  UriMemoryManagerStruct memoryManager;

  std::vector<uint8_t> uriData = provider.ConsumeRemainingBytes<uint8_t>();
  if (uriData.empty()) {
    return 0;
  }

  uriParseSingleUriExMmW(&uri, &afterLast, &charsRequired, &firstSyntaxErrorPos, &memoryManager);

  return 0;
}