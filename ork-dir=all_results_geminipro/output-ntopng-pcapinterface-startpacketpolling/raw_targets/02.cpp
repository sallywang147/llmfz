#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "pcap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* device = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();
  const int snaplen = stream.ConsumeIntegralInRange<int>(0, 1000);
  const int promisc = stream.ConsumeBool() ? 1 : 0;
  const int to_ms = stream.ConsumeIntegralInRange<int>(0, 1000);
  const char* errbuf = nullptr;

  pcap_t* pcap = pcap_create(device, errbuf);
  if (pcap == nullptr) {
    return 0;
  }

  if (pcap_set_snaplen(pcap, snaplen) != 0) {
    pcap_close(pcap);
    return 0;
  }

  if (pcap_set_promisc(pcap, promisc) != 0) {
    pcap_close(pcap);
    return 0;
  }

  if (pcap_set_timeout(pcap, to_ms) != 0) {
    pcap_close(pcap);
    return 0;
  }

  PcapInterface pcap_interface(pcap);
  pcap_interface.startPacketPolling();
  pcap_close(pcap);
  return 0;
}