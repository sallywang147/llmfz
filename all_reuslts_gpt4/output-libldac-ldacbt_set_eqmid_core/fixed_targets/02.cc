#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ldacBT.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _st_ldacbt_handle hLdacBT;
  int eqmid = stream.ConsumeIntegral<int>();

  ldacBT_set_eqmid_core(&hLdacBT, eqmid);

  return 0;
}