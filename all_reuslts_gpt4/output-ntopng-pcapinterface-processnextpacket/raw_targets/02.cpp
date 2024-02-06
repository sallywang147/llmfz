#include <fuzzer/FuzzedDataProvider.h>
#include <pcap.h>
#include <cstddef>
#include <cstdint>

#include "PcapInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a PcapInterface object
  PcapInterface pcapInterface;

  // Create a pcap object
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *pd = pcap_open_dead(DLT_EN10MB, 65535);
  if (pd == nullptr) {
    return 0;
  }

  // Get if_index and pcap_datalink_type from the stream
  int if_index = stream.ConsumeIntegral<int>();
  int pcap_datalink_type = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  pcapInterface.processNextPacket(&pcapInterface, pd, if_index, pcap_datalink_type);

  // Clean up
  pcap_close(pd);

  return 0;
}