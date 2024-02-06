#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "PcapInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  // Create a PcapInterface object
  PcapInterface pcapInterface;

  // Start packet polling
  pcapInterface.startPacketPolling(&pcapInterface);

  return 0;
}