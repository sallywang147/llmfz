#include "ldacBT.h"
#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _st_ldacbt_handle *hLdacBT = ldacBT_get_handle();
  ldacBT_get_error_code(hLdacBT);
  ldacBT_close_handle(hLdacBT);
  ldacBT_free_handle(hLdacBT);
  return 0;
}