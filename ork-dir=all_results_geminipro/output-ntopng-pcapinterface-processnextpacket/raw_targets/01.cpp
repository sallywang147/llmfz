#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pcap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct pcap* pd = pcap_open_offline_mem(data, size, PCAP_OPENFLAG_MAXLEN);
  if (pd == nullptr) {
    return 0;
  }

  PcapInterface* pcap_interface = new PcapInterface(pd);

  const int if_index = provider.ConsumeIntegral<int>();
  const int pcap_datalink_type = provider.ConsumeIntegral<int>();

  pcap_interface->processNextPacket(pcap_interface, pd, if_index,
                                    pcap_datalink_type);

  pcap_close(pd);
  delete pcap_interface;

  return 0;
}