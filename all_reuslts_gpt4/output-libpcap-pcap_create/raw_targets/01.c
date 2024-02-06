#include <fuzzer/FuzzedDataProvider.h>
#include <pcap/pcap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string device = stream.ConsumeRandomLengthString();
  char errbuf[PCAP_ERRBUF_SIZE];

  struct pcap *p = pcap_create(device.c_str(), errbuf);

  if (p != NULL) {
    pcap_close(p);
  }

  return 0;
}