#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lwan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lwan l;
  struct lwan_config config;

  // Initialize config with default values
  lwan_config_init(&config);

  // Fuzz some of the config values
  config.keep_alive_timeout = stream.ConsumeIntegralInRange<int>(0, 100);
  config.max_post_data_size = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  config.thread.count = stream.ConsumeIntegralInRange<int>(0, 100);
  config.thread.affinity = stream.ConsumeBool();

  // Initialize lwan with the fuzzed config
  lwan_init_with_config(&l, &config);

  // Clean up
  lwan_shutdown(&l);

  return 0;
}