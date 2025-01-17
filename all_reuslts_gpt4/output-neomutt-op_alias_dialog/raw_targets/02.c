#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mutt/mutt.h"

struct IndexSharedData {
  int dummy;
};

struct IndexPrivateData {
  int dummy;
};

extern int op_alias_dialog(struct IndexSharedData *, struct IndexPrivateData *, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct IndexSharedData sharedData;
  struct IndexPrivateData privateData;
  int arg = stream.ConsumeIntegral<int>();

  op_alias_dialog(&sharedData, &privateData, arg);

  return 0;
}