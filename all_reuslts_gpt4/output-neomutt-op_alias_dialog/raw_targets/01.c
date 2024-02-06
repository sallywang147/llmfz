#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mutt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct IndexSharedData sharedData;
  struct IndexPrivateData privateData;
  int integer = stream.ConsumeIntegral<int>();

  op_alias_dialog(&sharedData, &privateData, integer);

  return 0;
}