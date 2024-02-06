#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ldacBT.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize LDACBT handle
  struct _st_ldacbt_handle *hLdacBT = ldacBT_get_handle();
  if (hLdacBT == NULL) {
    return 0;
  }

  // Extract EQMID value
  int eqmid = stream.ConsumeIntegral<int>();

  // Call the target function
  ldacBT_set_eqmid_core(hLdacBT, eqmid);

  // Free the LDACBT handle
  ldacBT_free_handle(hLdacBT);

  return 0;
}