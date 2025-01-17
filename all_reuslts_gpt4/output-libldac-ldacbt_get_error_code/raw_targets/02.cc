#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "ldacBT.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize a _st_ldacbt_handle object
  struct _st_ldacbt_handle hLdacBT;
  size_t consumed = stream.ConsumeData(&hLdacBT, sizeof(hLdacBT));

  // If not enough data to populate the struct, return early
  if (consumed != sizeof(hLdacBT)) {
    return 0;
  }

  // Call the function to fuzz
  ldacBT_get_error_code(&hLdacBT);

  return 0;
}