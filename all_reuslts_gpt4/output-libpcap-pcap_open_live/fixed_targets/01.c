#include <pcap/pcap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int snaplen = stream.ConsumeIntegral<int>();
  int promisc = stream.ConsumeIntegral<int>();
  int to_ms = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string device = stream.ConsumeRandomLengthString();
  char *device_ptr = device.c_str();

  // Define errbuf
  char errbuf[PCAP_ERRBUF_SIZE];

  // Call the function
  struct pcap *pcap_handle = pcap_open_live(device_ptr, snaplen, promisc, to_ms, errbuf);

  // Close the pcap handle if it was successfully opened
  if (pcap_handle != NULL) {
    pcap_close(pcap_handle);
  }

  return 0;
}