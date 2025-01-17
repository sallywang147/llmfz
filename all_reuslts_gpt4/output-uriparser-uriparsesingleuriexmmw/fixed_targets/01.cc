#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "uriparser/Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  UriUriStructW uri;
  int errorPos, errorCode;
  int* elementLengths = nullptr;
  UriMemoryManagerStruct memoryManager;

  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());
  wchar_t *ptr = reinterpret_cast<wchar_t*>(bytes.data());

  uriParseSingleUriExMmW(&uri, &errorCode, &errorPos, &elementLengths, &memoryManager);

  return 0;
}