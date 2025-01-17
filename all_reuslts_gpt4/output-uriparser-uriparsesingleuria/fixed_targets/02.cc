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
  char *uriString = const_cast<char *>(str.c_str());

  UriUriStructA uri;
  char *errorMessage;

  int result = uriParseSingleUriA(&uri, uriString, &errorMessage);

  uriFreeUriMembersA(&uri);

  return 0;
}