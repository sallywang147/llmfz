#include <ldacBT_api.h>
#include "ldacBT.h"
#include <stddef.h>
#include <stdint.h>

#include <fuzzer/FuzzedDataProvider.h>

constexpr int32_t kEqmidValue[] = {LDACBT_EQMID_HQ, LDACBT_EQMID_SQ, LDACBT_EQMID_MQ};

extern "C" {
#include <ldacBT_api.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  HANDLE_LDAC_BT hLdacBT = ldacBT_get_handle();
  int32_t priority = stream.PickValueInArray(kEqmidValue);
  ldacBT_alter_eqmid_priority(hLdacBT, priority);
  ldacBT_close_handle(hLdacBT);
  ldacBT_free_handle(hLdacBT);
  return 0;
}