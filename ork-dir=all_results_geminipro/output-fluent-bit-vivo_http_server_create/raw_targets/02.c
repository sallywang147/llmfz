#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "vivo_exporter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const char* listen_address = stream.ConsumeRemainingBytesAsString().c_str();
  const int tcp_port = stream.ConsumeIntegral<int>();

  struct vivo_exporter* ctx = vivo_exporter_create();
  if (ctx == nullptr) {
    return 0;
  }

  struct flb_config* config = flb_config_create();
  if (config == nullptr) {
    vivo_exporter_destroy(ctx);
    return 0;
  }

  struct prom_http* http = vivo_http_server_create(ctx,
                                                    const_cast<char*>(listen_address),
                                                    tcp_port, config);
  if (http == nullptr) {
    vivo_exporter_destroy(ctx);
    flb_config_destroy(config);
    return 0;
  }

  vivo_http_server_destroy(http);
  flb_config_destroy(config);
  vivo_exporter_destroy(ctx);
  return 0;
}