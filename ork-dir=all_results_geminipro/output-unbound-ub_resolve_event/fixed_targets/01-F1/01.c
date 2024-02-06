#include "ub/ub.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <stdlib.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ub_ctx *ctx = ub_ctx_new();
  char *name = stream.ConsumeRandomLengthString();
  int rrtype = stream.ConsumeIntegral<int>();
  int rrclass = stream.ConsumeIntegral<int>();
  char *mydata = stream.ConsumeRandomLengthString();
  func_type *callback = stream.ConsumeIntegral<func_type *>();
  int *async_id = stream.ConsumeIntegral<int *>();

  int result = ub_resolve_event(ctx, name, rrtype, rrclass, mydata, callback, async_id);

  ub_ctx_delete(ctx);
  free(name);
  free(mydata);

  return result;
}