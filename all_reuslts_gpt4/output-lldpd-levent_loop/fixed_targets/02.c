#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lldpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lldpd *cfg = (struct lldpd*) calloc(1, sizeof(struct lldpd));
  if (!cfg) {
    return 0;
  }

  // Fuzzing the configuration
  cfg->g_config.c_mgmt_pattern = stream.ConsumeIntegral<int>();
  cfg->g_config.c_cid_pattern = stream.ConsumeIntegral<int>();
  cfg->g_config.c_pid_pattern = stream.ConsumeIntegral<int>();
  cfg->g_config.c_ttl_pattern = stream.ConsumeIntegral<int>();
  cfg->g_config.c_smart = stream.ConsumeBool();
  cfg->g_config.c_receiveonly = stream.ConsumeBool();
  cfg->g_config.c_protocol = stream.ConsumeIntegral<uint8_t>();
  cfg->g_config.c_paused = stream.ConsumeBool();
  cfg->g_config.c_tx_interval = stream.ConsumeIntegral<int>();
  cfg->g_config.c_tx_hold = stream.ConsumeIntegral<int>();
  cfg->g_config.c_max_neighbors = stream.ConsumeIntegral<int>();
  cfg->g_config.c_advertise_version = stream.ConsumeIntegral<int>();
  cfg->g_config.c_tx_fast = stream.ConsumeIntegral<int>();
  cfg->g_config.c_tx_fast_interval = stream.ConsumeIntegral<int>();
  cfg->g_config.c_shutdown = stream.ConsumeBool();

  // Call the function to fuzz
  levent_loop(cfg);

  free(cfg);

  return 0;
}