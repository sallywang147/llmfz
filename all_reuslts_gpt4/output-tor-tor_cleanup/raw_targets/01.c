#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "tor/or.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function tor_cleanup() does not take any parameters, we do not need to use FuzzedDataProvider.
  // The function is simply called.
  tor_cleanup();

  return 0;
}