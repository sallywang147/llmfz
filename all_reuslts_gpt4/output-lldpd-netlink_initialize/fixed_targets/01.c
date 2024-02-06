#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lldpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lldpd cfg;

  // Initialize the structure with fuzzed data
  cfg.g_config.c_mgmt_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_cid_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_iface_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_lldp_agent_type = stream.ConsumeIntegral<uint8_t>();
  cfg.g_config.c_lldp_tx_interval = stream.ConsumeIntegral<uint16_t>();
  cfg.g_config.c_lldp_tx_hold = stream.ConsumeIntegral<uint16_t>();
  cfg.g_config.c_lldp_tx_reinit_delay = stream.ConsumeIntegral<uint16_t>();

  // Call the function to fuzz
  netlink_initialize(&cfg);

  return 0;
}