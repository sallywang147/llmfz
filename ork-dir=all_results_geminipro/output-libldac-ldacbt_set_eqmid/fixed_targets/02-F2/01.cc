#include <stddef.h>
#include <stdint.h>
#include "ldacBT.h"

#include <fuzzer/FuzzedDataProvider.h>

constexpr LDACBT_EQMID_T kEqmidValue[] = {LDACBT_EQMID_HQ, LDACBT_EQMID_SQ, LDACBT_EQMID_MQ};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  HANDLE_LDAC_BT hLdacBT = ldacBT_get_handle();
  if (hLdacBT == nullptr) {
    return 0;
  }

  int eqmid = stream.PickValueInArray(kEqmidValue);
  int status = ldacBT_set_eqmid(hLdacBT, eqmid);
  if (!status) {
    return 0;
  }

  ldacBT_close_handle(hLdacBT);
  ldacBT_free_handle(hLdacBT);
  return 0;
}