#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "dhcp_serv.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct dhcp_config config;
  memset(&config, 0, sizeof(config));

  config.ip_pool_start = provider.ConsumeIntegral<uint32_t>();
  config.ip_pool_end = provider.ConsumeIntegral<uint32_t>();
  config.lease_time = provider.ConsumeIntegral<uint32_t>();
  config.renewal_time = provider.ConsumeIntegral<uint32_t>();
  config.rebinding_time = provider.ConsumeIntegral<uint32_t>();
  config.max_leases = provider.ConsumeIntegral<uint32_t>();
  config.subnet_mask = provider.ConsumeIntegral<uint32_t>();
  config.router = provider.ConsumeIntegral<uint32_t>();
  config.dns_server = provider.ConsumeIntegral<uint32_t>();
  config.domain_name = provider.ConsumeBytes<char>(provider.ConsumeIntegralInRange<size_t>(0, size));

  // Fix: Check if the domain name is empty before using it.
  if (config.domain_name[0] == '\0') {
    config.domain_name = nullptr;
  }

  dhserv_init(&config);

  dhserv_run();

  return 0;
}