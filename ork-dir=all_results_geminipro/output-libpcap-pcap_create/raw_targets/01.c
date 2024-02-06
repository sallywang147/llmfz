#include <fuzzer/FuzzedDataProvider.h>

#include <pcap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t device_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  auto device = provider.ConsumeBytes<char>(device_size);
  size_t errbuf_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  auto errbuf = provider.ConsumeBytes<char>(errbuf_size);

  pcap_create((char *)device.data(), (char *)errbuf.data());

  return 0;
}