#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "uriparser/Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize the UriUriStructA object
  UriUriStructA uriStruct;
  uriStruct.absolutePath = stream.ConsumeBool();
  uriStruct.hostText.first = nullptr;
  uriStruct.hostText.afterLast = nullptr;
  uriStruct.scheme.first = nullptr;
  uriStruct.scheme.afterLast = nullptr;
  uriStruct.userInfo.first = nullptr;
  uriStruct.userInfo.afterLast = nullptr;
  uriStruct.portText.first = nullptr;
  uriStruct.portText.afterLast = nullptr;
  uriStruct.query.first = nullptr;
  uriStruct.query.afterLast = nullptr;
  uriStruct.fragment.first = nullptr;
  uriStruct.fragment.afterLast = nullptr;
  
  // Initialize the errorPos pointer
  char* errorPos = nullptr;

  // Get the input string
  std::string inputString = stream.ConsumeRemainingBytesAsString();
  char* input = const_cast<char*>(inputString.c_str());

  // Call the target function
  int result = uriParseSingleUriExA(&uriStruct, input, input + inputString.size(), &errorPos);

  // Clean up
  uriFreeUriMembersA(&uriStruct);

  return 0;
}