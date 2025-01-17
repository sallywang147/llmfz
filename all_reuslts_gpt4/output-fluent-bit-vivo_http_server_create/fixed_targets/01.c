#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fluent-bit/flb_config.h"
#include "fluent-bit/flb_exporter.h"
#include "fluent-bit/flb_prom.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct flb_config* config = flb_config_init();
  if (config == NULL) {
    return 0;
  }

  struct vivo_exporter* ctx = flb_exporter_prometheus_init(config, NULL);
  if (ctx == NULL) {
    flb_config_exit(config);
    return 0;
  }

  std::string listen = stream.ConsumeRandomLengthString();
  int tcp_port = stream.ConsumeIntegral<int>();

  struct prom_http* http = vivo_http_server_create(ctx, const_cast<char*>(listen.c_str()), tcp_port, config);

  if (http != NULL) {
    prom_http_server_destroy(http);
  }
  
  flb_exporter_prometheus_exit(ctx, config);
  flb_config_exit(config);
  
  return 0;
}