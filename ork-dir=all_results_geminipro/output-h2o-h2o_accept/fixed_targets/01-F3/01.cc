#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint16_t port = stream.ConsumeIntegral<uint16_t>();
  const uint16_t backlog = stream.ConsumeIntegral<uint16_t>();
  const std::string host = stream.ConsumeRemainingBytesAsString();

  struct st_h2o_accept_ctx_t accept_ctx;
  memset(&accept_ctx, 0, sizeof(accept_ctx));
  h2o_accept(&accept_ctx, nullptr);

  return 0;
}