#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vivo_exporter.h"
#include "fluent-bit/flb_config.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct flb_config *config;
  struct vivo_exporter *ctx;
  struct prom_http *http_server;
  int tcp_port;
  std::string listen;

  FuzzedDataProvider stream(data, size);

  // Initialize the Fluent Bit config
  config = flb_config_init();
  if (config == NULL) {
    return 0;
  }

  // Initialize the Vivo exporter
  ctx = vivo_exporter_create(config);
  if (ctx == NULL) {
    flb_config_exit(config);
    return 0;
  }

  // Extract the TCP port
  tcp_port = stream.ConsumeIntegral<int>();

  // Extract the listen string
  listen = stream.ConsumeRandomLengthString();
  
  // Create the HTTP server
  http_server = vivo_http_server_create(ctx, const_cast<char*>(listen.c_str()), tcp_port, config);
  
  // Cleanup
  if (http_server != NULL) {
    vivo_http_server_destroy(http_server);
  }
  vivo_exporter_destroy(ctx);
  flb_config_exit(config);

  return 0;
}