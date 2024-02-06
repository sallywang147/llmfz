#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "uriparser/Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<int> vec = stream.ConsumeBytes<int>(stream.remaining_bytes());
  if (vec.empty()) {
    return 0;
  }
  int* errorPos = vec.data();

  UriUriStructW uri;
  uriParseSingleUriW(&uri, errorPos, &errorPos);

  uriFreeUriMembersW(&uri);

  return 0;
}