#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "uriparser/Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = &str[0];
  char* errorPos;

  UriUriStructA uri;
  uriParseSingleUriA(&uri, ptr, &errorPos);
  uriFreeUriMembersA(&uri);

  return 0;
}