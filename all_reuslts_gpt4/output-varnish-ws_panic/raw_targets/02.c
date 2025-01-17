#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cache/cache.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct vsb *vsb = VSB_new_auto();
  if (vsb == nullptr) {
    return 0;
  }

  struct ws *ws = WS_New();
  if (ws == nullptr) {
    VSB_delete(vsb);
    return 0;
  }

  WS_Panic(vsb, ws);

  WS_Delete(ws);
  VSB_delete(vsb);

  return 0;
}