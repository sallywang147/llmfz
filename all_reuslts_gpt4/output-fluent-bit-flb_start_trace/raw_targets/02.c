#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "flb_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct flb_lib_ctx *ctx = flb_lib_init("tcp://127.0.0.1:5140");
  if (ctx == NULL) {
    return 0;
  }

  // Consume data to fill the trace
  while (stream.remaining_bytes() > 0) {
    std::string trace_data = stream.ConsumeRandomLengthString();
    flb_lib_push(ctx, trace_data.c_str(), trace_data.size());
  }

  flb_start_trace(ctx);

  flb_lib_exit(ctx);

  return 0;
}