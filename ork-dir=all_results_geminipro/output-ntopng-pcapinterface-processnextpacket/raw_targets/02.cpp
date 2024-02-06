#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "pcap.h"

class PcapInterface {
 public:
  bool processNextPacket(struct pcap* pd, int if_index, int pcap_datalink_type) {
    FuzzedDataProvider stream(data, size);
    const size_t packet_size =
        stream.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
    std::vector<uint8_t> packet(packet_size);
    stream.ConsumeBytes<uint8_t>(packet.data(), packet_size);
    return pcap_process_packet(pd, packet.data(), packet_size) == 1;
  }

 private:
  const uint8_t* data;
  size_t size;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  PcapInterface pcap_interface;
  pcap_interface.processNextPacket(nullptr, 0, 0);
  return 0;
}