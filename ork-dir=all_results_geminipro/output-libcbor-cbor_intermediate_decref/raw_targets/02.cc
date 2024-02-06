#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cbor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  cbor_load_result result;
  cbor_item_t *item = cbor_load(Data, Size, &result);
  if (result.error.code == CBOR_ERR_NONE) {
    cbor_intermediate_decref(item);
    cbor_decref(&item);
  }
  return 0;
}