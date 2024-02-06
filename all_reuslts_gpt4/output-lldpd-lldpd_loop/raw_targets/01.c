#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lldpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the lldpd struct
  struct lldpd cfg;
  
  // Fill the lldpd struct with fuzzed data
  cfg.g_config.c_mgmt_pattern = stream.ConsumeIntegral<int>();
  cfg.g_config.c_max_neighbors = stream.ConsumeIntegral<int>();
  cfg.g_config.c_cid_len = stream.ConsumeIntegral<int>();
  cfg.g_config.c_paused = stream.ConsumeBool();
  cfg.g_config.c_receiveonly = stream.ConsumeBool();
  
  // Call the function under test
  lldpd_loop(&cfg);

  return 0;
}