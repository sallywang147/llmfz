#include <fuzzer/FuzzedDataProvider.h>
#include "ldacBT.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize LDACBT handle
  struct _st_ldacbt_handle *hLdacBT = ldacBT_get_handle();
  if (hLdacBT == NULL) {
    return 0;
  }

  // Consume data from the fuzzer input
  int priority = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  ldacBT_alter_eqmid_priority(hLdacBT, priority);

  // Free the LDACBT handle
  ldacBT_free_handle(hLdacBT);

  return 0;
}