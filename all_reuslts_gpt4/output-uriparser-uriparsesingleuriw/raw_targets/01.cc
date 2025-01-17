#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "uriparser/Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize UriUriStructW
  UriUriStructW uriStruct;
  uriStruct.absolutePath = stream.ConsumeBool();
  uriStruct.hostData.ip4 = stream.ConsumeIntegral<unsigned char>();
  uriStruct.hostData.ip6 = stream.ConsumeIntegral<unsigned short>();
  uriStruct.hostData.ipFuture.first = stream.ConsumeIntegral<unsigned char>();
  uriStruct.hostData.ipFuture.afterLast = stream.ConsumeIntegral<unsigned char>();
  uriStruct.hostText.first = stream.ConsumeIntegral<wchar_t>();
  uriStruct.hostText.afterLast = stream.ConsumeIntegral<wchar_t>();
  uriStruct.owner = stream.ConsumeIntegral<UriUriStructA*>();
  uriStruct.portText.first = stream.ConsumeIntegral<wchar_t>();
  uriStruct.portText.afterLast = stream.ConsumeIntegral<wchar_t>();
  uriStruct.query.first = stream.ConsumeIntegral<wchar_t>();
  uriStruct.query.afterLast = stream.ConsumeIntegral<wchar_t>();
  uriStruct.scheme.first = stream.ConsumeIntegral<wchar_t>();
  uriStruct.scheme.afterLast = stream.ConsumeIntegral<wchar_t>();
  uriStruct.userInfo.first = stream.ConsumeIntegral<wchar_t>();
  uriStruct.userInfo.afterLast = stream.ConsumeIntegral<wchar_t>();

  // Initialize int *
  int errorCode = stream.ConsumeIntegral<int>();
  int *errorCodePtr = &errorCode;

  // Initialize int **
  int errorPos = stream.ConsumeIntegral<int>();
  int *errorPosPtr = &errorPos;
  int **errorPosPtrPtr = &errorPosPtr;

  // Call the function to fuzz
  uriParseSingleUriW(&uriStruct, errorCodePtr, errorPosPtrPtr);

  return 0;
}