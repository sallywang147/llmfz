#include <pcap/pcap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate random values for function arguments
  std::string device = stream.ConsumeRandomLengthString(16);
  int snaplen = stream.ConsumeIntegralInRange<int>(0, 1024);
  int promisc = stream.ConsumeBool() ? 1 : 0;
  int to_ms = stream.ConsumeIntegralInRange<int>(0, 1000);
  std::string errbuf = stream.ConsumeRandomLengthString(16);

  // Call the function with the generated arguments
  struct pcap *pcap_handle = pcap_open_live(device.c_str(), snaplen, promisc, to_ms, errbuf.c_str());

  // Close the PCAP handle if it was successfully opened
  if (pcap_handle != nullptr) {
    pcap_close(pcap_handle);
  }

  return 0;
}