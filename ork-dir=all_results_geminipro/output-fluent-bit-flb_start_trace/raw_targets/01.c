#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "flb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct flb_lib_ctx* ctx = flb_create_ctx();
  flb_start_trace(ctx);

  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  flb_write_trace(ctx, bytes.data(), bytes.size());
  flb_stop_trace(ctx);
  flb_destroy_ctx(ctx);
  return 0;
}