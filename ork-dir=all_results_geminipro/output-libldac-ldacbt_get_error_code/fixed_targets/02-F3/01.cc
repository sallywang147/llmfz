#include "ldacBT.h"
#include <stddef.h>
#include <stdint.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <ldacBT_api.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ldacBT_handle_t handle = ldacBT_init();
  ldacBT_get_error_code(handle);
  ldacBT_deinit(handle);
  return 0;
}