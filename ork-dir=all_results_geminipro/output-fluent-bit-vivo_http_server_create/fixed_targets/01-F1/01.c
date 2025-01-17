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
  const std::string listen = stream.ConsumeRemainingBytesAsString();
  const int tcp_port = stream.ConsumeIntegral<int>();
  struct flb_config config;
  struct vivo_exporter ctx;
  vivo_http_server_create(&ctx, const_cast<char*>(listen.c_str()), tcp_port, &config);
  return 0;
}