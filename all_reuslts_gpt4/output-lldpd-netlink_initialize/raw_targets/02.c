#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "lldpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct lldpd cfg;
  FuzzedDataProvider stream(data, size);

  // Initialize the struct with fuzzed data
  cfg.g_config.c_mgmt_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_cid_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_iface_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_descr_override = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_platform_override = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_disable_coe = stream.ConsumeBool();
  cfg.g_config.c_enable_lldp = stream.ConsumeBool();
  cfg.g_config.c_enable_dot1 = stream.ConsumeBool();
  cfg.g_config.c_enable_dot3 = stream.ConsumeBool();
  cfg.g_config.c_enable_med = stream.ConsumeBool();
  cfg.g_config.c_paused = stream.ConsumeBool();
  cfg.g_config.c_tx_interval = stream.ConsumeIntegral<int>();
  cfg.g_config.c_tx_hold = stream.ConsumeIntegral<int>();
  cfg.g_config.c_max_neighbors = stream.ConsumeIntegral<int>();
  cfg.g_config.c_active = stream.ConsumeBool();
  cfg.g_config.c_receiveonly = stream.ConsumeBool();
  cfg.g_config.c_smart = stream.ConsumeBool();
  cfg.g_config.c_hide_unknown = stream.ConsumeBool();
  cfg.g_config.c_advertise_version = stream.ConsumeBool();
  cfg.g_config.c_set_ifdescr = stream.ConsumeBool();
  cfg.g_config.c_set_ifname = stream.ConsumeBool();
  cfg.g_config.c_read_sys_descr = stream.ConsumeBool();
  cfg.g_config.c_read_sys_name = stream.ConsumeBool();
  cfg.g_config.c_read_port_descr = stream.ConsumeBool();
  cfg.g_config.c_mgmt = stream.ConsumeIntegral<int>();
  cfg.g_config.c_cid = stream.ConsumeIntegral<int>();
  cfg.g_config.c_iface = stream.ConsumeIntegral<int>();
  cfg.g_config.c_descr = stream.ConsumeIntegral<int>();
  cfg.g_config.c_platform = stream.ConsumeIntegral<int>();
  cfg.g_config.c_noinitial = stream.ConsumeBool();
  cfg.g_config.c_nodaemon = stream.ConsumeBool();
  cfg.g_config.c_bond_slave_src_mac_type = stream.ConsumeIntegral<int>();
  cfg.g_config.c_bond_slave_src_mac = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_bond_vlan = stream.ConsumeIntegral<int>();
  cfg.g_config.c_bond_vlan_prio = stream.ConsumeIntegral<int>();
  cfg.g_config.c_bond_vlan_dei = stream.ConsumeBool();

  // Call the function to fuzz
  netlink_initialize(&cfg);

  return 0;
}