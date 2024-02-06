#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct UriUriStructW uri;
  int errorPos = stream.ConsumeIntegral<int>();
  int firstNonZero = stream.ConsumeIntegral<int>();
  std::vector<int> vec = stream.ConsumeRemainingBytes<int>();
  int* intPtr = vec.data();

  uriParseSingleUriExW(&uri, &errorPos, &firstNonZero, &intPtr);

  return 0;
}