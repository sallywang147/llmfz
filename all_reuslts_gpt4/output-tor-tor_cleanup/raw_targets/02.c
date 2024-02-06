#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "orconfig.h"
#include "src/lib/libtor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // The function tor_cleanup() does not take any arguments, so we don't need to use FuzzedDataProvider.
  // We simply call the function.
  tor_cleanup();

  return 0;
}