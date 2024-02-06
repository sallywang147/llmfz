#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "mutt/mutt.h"

struct IndexSharedData {
  int dummy;
};

struct IndexPrivateData {
  int dummy;
};

extern "C" int op_post(struct IndexSharedData * , struct IndexPrivateData * , int );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct IndexSharedData sharedData;
  struct IndexPrivateData privateData;
  int int_arg = stream.ConsumeIntegral<int>();

  op_post(&sharedData, &privateData, int_arg);

  return 0;
}