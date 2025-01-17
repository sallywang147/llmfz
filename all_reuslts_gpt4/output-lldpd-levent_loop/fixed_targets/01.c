#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "lldpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the lldpd struct
  struct lldpd cfg;

  // Fill the struct with fuzzed data
  cfg.g_config.c_mgmt_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_cid_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_iface_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_descr_override = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_platform_override = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_systemid = stream.ConsumeIntegral<uint8_t>();
  cfg.g_config.c_ttl = stream.ConsumeIntegral<uint16_t>();
  cfg.g_config.c_advertise_version = stream.ConsumeBool();
  cfg.g_config.c_receiveonly = stream.ConsumeBool();
  cfg.g_config.c_paused = stream.ConsumeBool();
  cfg.g_config.c_tx_interval = stream.ConsumeIntegral<uint16_t>();
  cfg.g_config.c_smart = stream.ConsumeIntegral<int>();
  cfg.g_config.c_max_neighbors = stream.ConsumeIntegral<int>();

  // Call the target function
  levent_loop(&cfg);

  return 0;
}