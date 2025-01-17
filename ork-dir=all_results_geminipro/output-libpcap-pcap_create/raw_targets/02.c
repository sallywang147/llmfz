#include <fuzzer/FuzzedDataProvider.h>

#include <pcap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t device_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  auto device_input = provider.ConsumeBytes<char>(device_size);
  std::string device(device_input.data(), device_input.size());

  size_t errbuf_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  auto errbuf_input = provider.ConsumeBytes<char>(errbuf_size);
  std::string errbuf(errbuf_input.data(), errbuf_input.size());

  pcap_create(device.c_str(), errbuf.c_str());

  return 0;
}