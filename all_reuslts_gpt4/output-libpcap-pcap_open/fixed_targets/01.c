#include <pcap/pcap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Prepare parameters for pcap_open
  std::string source = stream.ConsumeRandomLengthString();
  int snaplen = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();
  int read_timeout = stream.ConsumeIntegral<int>();
  struct pcap_rmtauth auth;
  char errbuf[PCAP_ERRBUF_SIZE];

  // Initialize auth struct
  auth.type = stream.ConsumeIntegral<int>();
  auth.username = const_cast<char *>(stream.ConsumeRandomLengthString().c_str());
  auth.password = const_cast<char *>(stream.ConsumeRandomLengthString().c_str());

  // Call pcap_open
  struct pcap *pcap_handle = pcap_open(source.c_str(), snaplen, flags, read_timeout, &auth, errbuf);

  if (pcap_handle) {
    pcap_close(pcap_handle);
  }

  return 0;
}