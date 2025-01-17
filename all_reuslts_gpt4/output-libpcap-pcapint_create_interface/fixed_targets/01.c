#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/pcap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string device = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string ebuf = stream.ConsumeRemainingBytesAsString();

  pcap_t *pcap = pcapint_create_interface(device.c_str(), ebuf.c_str());
  if (pcap != NULL) {
    pcap_close(pcap);
  }

  return 0;
}