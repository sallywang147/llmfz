#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ldacBT.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the LDACBT handle
  _st_ldacbt_handle* hLdacBT = ldacBT_get_handle();
  if (hLdacBT == nullptr) {
    return 0;
  }

  // Extract the priority value
  int priority = stream.ConsumeIntegral<int>();

  // Call the target function
  ldacBT_alter_eqmid_priority(hLdacBT, priority);

  // Free the LDACBT handle
  ldacBT_free_handle(hLdacBT);

  return 0;
}