#include <fuzzer/FuzzedDataProvider.h>
#include <pcap.h>
#include <cstdint>
#include <cstddef>

#include "PcapInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the PcapInterface
  PcapInterface pcapInterface;

  // Create a pcap_t structure
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *pd = pcap_open_dead(DLT_EN10MB, 65535);
  if (!pd) {
    return 0;
  }

  // Consume data for if_index and pcap_datalink_type
  int if_index = stream.ConsumeIntegral<int>();
  int pcap_datalink_type = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  pcapInterface.processNextPacket(&pcapInterface, pd, if_index, pcap_datalink_type);

  // Clean up
  pcap_close(pd);

  return 0;
}