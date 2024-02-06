#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ZMQCollectorInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize ZMQCollectorInterface
  ZMQCollectorInterface interface;

  // Call the function to fuzz
  interface.startPacketPolling(&interface);

  return 0;
}