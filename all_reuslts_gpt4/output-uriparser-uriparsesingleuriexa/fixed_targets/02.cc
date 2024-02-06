#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "uriparser/Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize UriUriStructA
  UriUriStructA uriStruct;
  uriStruct.scheme.first = nullptr;
  uriStruct.scheme.afterLast = nullptr;
  uriStruct.userInfo.first = nullptr;
  uriStruct.userInfo.afterLast = nullptr;
  uriStruct.hostText.first = nullptr;
  uriStruct.hostText.afterLast = nullptr;
  uriStruct.portText.first = nullptr;
  uriStruct.portText.afterLast = nullptr;
  uriStruct.pathHead = nullptr;
  uriStruct.pathTail = nullptr;
  uriStruct.query.first = nullptr;
  uriStruct.query.afterLast = nullptr;
  uriStruct.fragment.first = nullptr;
  uriStruct.fragment.afterLast = nullptr;
  uriStruct.owner = nullptr;
  uriStruct.absolutePath = false;

  // Initialize char pointers
  char* chars = nullptr;
  char* charsEnd = nullptr;
  char* errorPos = nullptr;

  // Consume data from the stream
  std::string str = stream.ConsumeRemainingBytesAsString();
  chars = const_cast<char*>(str.c_str());
  charsEnd = chars + str.size();

  // Call the function to fuzz
  int result = uriParseSingleUriExA(&uriStruct, chars, charsEnd, &errorPos);

  // Free memory
  uriFreeUriMembersA(&uriStruct);

  return 0;
}