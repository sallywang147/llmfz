#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t hostname_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
  size_t hostname_port_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
  size_t service_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
  size_t transport_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
  size_t ttl_size = provider.ConsumeIntegralInRange<size_t>(0, 100);

  std::string hostname = provider.ConsumeBytesAsString(hostname_size);
  std::string hostname_port = provider.ConsumeBytesAsString(hostname_port_size);
  std::string service = provider.ConsumeBytesAsString(service_size);
  std::string transport = provider.ConsumeBytesAsString(transport_size);
  std::string ttl = provider.ConsumeBytesAsString(ttl_size);

  addr_callback(hostname.c_str(), hostname_port.c_str(), service.c_str(),
                transport.c_str(), ttl.c_str());
}