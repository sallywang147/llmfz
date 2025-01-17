#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "lldpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lldpd cfg;
  // Consume data for each field in the struct
  cfg.g_config.c_mgmt_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_cid_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_pid_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_platform_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_descr_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_pattern_arg = stream.ConsumeIntegral<int>();
  cfg.g_config.c_receiveonly = stream.ConsumeIntegral<int>();
  cfg.g_config.c_smart = stream.ConsumeIntegral<int>();
  cfg.g_config.c_max_neighbors = stream.ConsumeIntegral<int>();
  cfg.g_config.c_paused = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_interval = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldpmed_noinventory = stream.ConsumeIntegral<int>();
  cfg.g_config.c_bond_slave_src_mac_type = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_lldp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_dot1 = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_dot3 = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_med = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_edp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_fdp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_sonmp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_custom = stream.ConsumeIntegral<int>();
  cfg.g_config.c_ttl = stream.ConsumeIntegral<int>();
  cfg.g_config.c_advertise_version = stream.ConsumeIntegral<int>();
  cfg.g_config.c_fallback_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_last_change = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_fast = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_fast_interval = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_fast_init = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_retries = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_type = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_size = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_allocated = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_index = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_lldp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_dot1 = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_dot3 = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_med = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_edp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_fdp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_sonmp = stream.ConsumeIntegral<int>();
  cfg.g_config.c_enable_custom = stream.ConsumeIntegral<int>();
  cfg.g_config.c_ttl = stream.ConsumeIntegral<int>();
  cfg.g_config.c_advertise_version = stream.ConsumeIntegral<int>();
  cfg.g_config.c_fallback_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_last_change = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_fast = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_fast_interval = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_fast_init = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_retries = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_type = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_size = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_allocated = stream.ConsumeIntegral<int>();
  cfg.g_config.c_lldp_agent_index = stream.ConsumeIntegral<int>();

  levent_init(&cfg);

  return 0;
}