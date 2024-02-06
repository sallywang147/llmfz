#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "dpif-netdev.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a dpif structure
  struct dpif dpif;
  
  // Populate the dpif structure with fuzzed data
  stream.ConsumeData(&dpif, sizeof(dpif));

  // Call the target function
  dpif_netdev_run(&dpif);

  return 0;
}