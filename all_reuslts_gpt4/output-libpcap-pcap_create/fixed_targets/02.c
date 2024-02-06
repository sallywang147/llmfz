#include <fuzzer/FuzzedDataProvider.h>
#include <pcap/pcap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string device = stream.ConsumeRandomLengthString();
  char errbuf[PCAP_ERRBUF_SIZE];

  struct pcap *pcap_handle = pcap_create(device.c_str(), errbuf);

  if (pcap_handle != NULL) {
    pcap_close(pcap_handle);
  }

  return 0;
}