 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "iter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct IterCellsResolution *res =
      (struct IterCellsResolution *)malloc(sizeof(struct IterCellsResolution));
  if (res == nullptr) {
    return 0;
  }
  iterInitRes(res, stream.ConsumeIntegral<int>());
  free(res);
  return 0;
}