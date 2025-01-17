#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ldacBT.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the _st_ldacbt_handle struct
  struct _st_ldacbt_handle handle;
  handle.magic = stream.ConsumeIntegral<int>();
  handle.id = stream.ConsumeIntegral<int>();
  handle.err_code = stream.ConsumeIntegral<int>();
  handle.err_category = stream.ConsumeIntegral<int>();
  handle.err_detail = stream.ConsumeIntegral<int>();
  handle.err_p1 = stream.ConsumeIntegral<int>();
  handle.err_p2 = stream.ConsumeIntegral<int>();
  handle.err_p3 = stream.ConsumeIntegral<int>();
  handle.err_p4 = stream.ConsumeIntegral<int>();

  // Call the function with the fuzzed data
  int result = ldacBT_get_error_code(&handle);

  return 0;
}