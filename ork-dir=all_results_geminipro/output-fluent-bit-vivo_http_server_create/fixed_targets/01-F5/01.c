#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "vivo_exporter.h"

extern "C" {
#include "flb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char* listen = strdup(stream.ConsumeRemainingBytesAsString().c_str());
  const int tcp_port = stream.ConsumeIntegral<int>();
  struct flb_config config;
  struct vivo_exporter ctx;
  vivo_http_server_create(&ctx, listen, tcp_port, &config);
  vivo_http_server_destroy(&ctx);  // Call vivo_http_server_destroy to free resources
  free(listen);
  return 0;
}