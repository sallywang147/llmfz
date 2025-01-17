#include <fuzzer/FuzzedDataProvider.h>

#include <pcap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate a random source string.
  std::string source = provider.ConsumeRandomLengthString(100);

  // Generate a random snaplen.
  int snaplen = provider.ConsumeIntegralInRange<int>(0, 1000);

  // Generate a random flags value.
  int flags = provider.ConsumeIntegralInRange<int>(0, 1000);

  // Generate a random read timeout value.
  int read_timeout = provider.ConsumeIntegralInRange<int>(0, 1000);

  // Generate a random auth value.
  struct pcap_rmtauth auth;
  provider.ConsumeData(&auth, sizeof(auth));

  // Generate a random errbuf value.
  char errbuf[PCAP_ERRBUF_SIZE];
  provider.ConsumeData(errbuf, sizeof(errbuf));

  // Call pcap_open with the generated values.
  pcap_t* handle = pcap_open(source.c_str(), snaplen, flags, read_timeout, &auth, errbuf);

  // If pcap_open succeeded, close the handle.
  if (handle != nullptr) {
    pcap_close(handle);
  }

  return 0;
}