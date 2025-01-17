#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <pcap.h>

#include "PcapInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a PcapInterface object
  PcapInterface pcapInterface;

  // Start packet polling on the PcapInterface object
  pcapInterface.startPacketPolling();

  return 0;
}