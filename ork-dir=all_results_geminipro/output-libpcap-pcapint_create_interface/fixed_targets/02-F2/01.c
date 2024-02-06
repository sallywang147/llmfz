#include <fuzzer/FuzzedDataProvider.h>
#include <pcap/pcap.h>

extern "C" {
#include <pcap/pcap.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t device_len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  size_t ebuf_len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  auto device = provider.ConsumeBytes<char>(device_len);
  auto ebuf = provider.ConsumeBytes<char>(ebuf_len);
  pcapint_create_interface(device.data(), ebuf.data());
  return 0;
}