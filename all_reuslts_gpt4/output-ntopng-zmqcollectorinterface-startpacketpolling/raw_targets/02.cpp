#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "ZMQCollectorInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create ZMQCollectorInterface object
  ZMQCollectorInterface collectorInterface;
  
  // Start packet polling
  collectorInterface.startPacketPolling(&collectorInterface);

  return 0;
}