#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "lwan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lwan l;
  struct lwan_config config;

  // Initialize the config with some default values.
  config.listener = "127.0.0.1:8080";
  config.thread.count = 1;
  config.thread.max_fd = 1024;
  config.thread.timeout = 10;
  config.thread.max_clients = 1024;
  config.expiration_timer = 1;
  config.keep_alive_timeout = 2;
  config.quiet = true;
  config.reuse_port = false;
  config.proxy_protocol = false;
  config.allow_cors = false;
  config.expires = 1;
  config.error_template = nullptr;
  config.config_file_path = nullptr;

  // Fuzz the configuration with the provided data.
  config.thread.count = stream.ConsumeIntegralInRange<int>(1, 100);
  config.thread.max_fd = stream.ConsumeIntegralInRange<int>(1, 1024);
  config.thread.timeout = stream.ConsumeIntegralInRange<int>(1, 100);
  config.thread.max_clients = stream.ConsumeIntegralInRange<int>(1, 1024);
  config.expiration_timer = stream.ConsumeIntegralInRange<int>(1, 100);
  config.keep_alive_timeout = stream.ConsumeIntegralInRange<int>(1, 100);
  config.expires = stream.ConsumeIntegralInRange<int>(1, 100);
  config.quiet = stream.ConsumeBool();
  config.reuse_port = stream.ConsumeBool();
  config.proxy_protocol = stream.ConsumeBool();
  config.allow_cors = stream.ConsumeBool();

  lwan_init_with_config(&l, &config);

  lwan_shutdown(&l);

  return 0;
}