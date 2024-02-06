#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dhcp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dhcp_config config;

  config.lease_time = stream.ConsumeIntegral<uint32_t>();
  config.max_lease_time = stream.ConsumeIntegral<uint32_t>();
  config.default_lease_time = stream.ConsumeIntegral<uint32_t>();
  config.bootp_dynamic = stream.ConsumeBool();
  config.bootp_static = stream.ConsumeBool();

  size_t subnet_size = stream.ConsumeIntegralInRange<size_t>(0, 10);
  for(size_t i = 0; i < subnet_size; ++i) {
    struct dhcp_subnet subnet;
    subnet.next = nullptr;
    subnet.prev = nullptr;
    subnet.interface = stream.ConsumeRandomLengthString().c_str();
    subnet.s_addr = stream.ConsumeIntegral<uint32_t>();
    subnet.s_addr = stream.ConsumeIntegral<uint32_t>();
    config.subnet = &subnet;
  }

  size_t pool_size = stream.ConsumeIntegralInRange<size_t>(0, 10);
  for(size_t i = 0; i < pool_size; ++i) {
    struct dhcp_pool pool;
    pool.next = nullptr;
    pool.prev = nullptr;
    pool.s_addr = stream.ConsumeIntegral<uint32_t>();
    pool.e_addr = stream.ConsumeIntegral<uint32_t>();
    config.pool = &pool;
  }

  size_t option_size = stream.ConsumeIntegralInRange<size_t>(0, 10);
  for(size_t i = 0; i < option_size; ++i) {
    struct dhcp_option option;
    option.next = nullptr;
    option.prev = nullptr;
    option.len = stream.ConsumeIntegral<uint8_t>();
    option.data = stream.ConsumeBytes<uint8_t>(option.len).data();
    config.option = &option;
  }

  dhserv_init(&config);

  return 0;
}