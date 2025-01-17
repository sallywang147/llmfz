#include "ldacBT.h"
#include <stddef.h>
#include <stdint.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  HANDLE_LDAC_BT handle_ldac_bt = ldacBT_get_handle();
  ldacBT_set_eqmid_core(handle_ldac_bt, stream.ConsumeIntegral<int>());
  ldacBT_free_handle(handle_ldac_bt);

  return 0;
}