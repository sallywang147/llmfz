#include <cstdint>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

extern "C" {
#include "dhcp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  // Create a dhcp_config struct.
  struct dhcp_config config;
  memset(&config, 0, sizeof(config));

  // Consume data from the provider and populate the dhcp_config struct.
  config.ip_addr = provider.ConsumeIntegral<uint32_t>();
  config.netmask = provider.ConsumeIntegral<uint32_t>();
  config.gateway = provider.ConsumeIntegral<uint32_t>();
  config.dns_server = provider.ConsumeIntegral<uint32_t>();
  config.lease_time = provider.ConsumeIntegral<uint32_t>();
  config.renewal_time = provider.ConsumeIntegral<uint32_t>();
  config.rebinding_time = provider.ConsumeIntegral<uint32_t>();

  // Consume a string and set the dhcp_config's hostname field.
  std::string hostname = provider.ConsumeRandomLengthString();
  config.hostname = hostname.c_str();

  // Call the dhserv_init function with the populated dhcp_config struct.
  int result = dhserv_init(&config);

  // Consume the remaining bytes from the provider.
  std::vector<uint8_t> remaining_bytes = provider.ConsumeRemainingBytes();

  return result;
}