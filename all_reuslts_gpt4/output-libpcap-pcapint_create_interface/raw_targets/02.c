#include <stdint.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
  #include <pcap/pcap.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string device = stream.ConsumeRandomLengthString();
  char ebuf[PCAP_ERRBUF_SIZE];

  struct pcap *pcap = pcapint_create_interface(device.c_str(), ebuf);

  if (pcap != NULL) {
    pcap_close(pcap);
  }

  return 0;
}