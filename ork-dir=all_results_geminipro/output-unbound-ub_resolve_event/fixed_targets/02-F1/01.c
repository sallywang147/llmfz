#include <fuzzer/FuzzedDataProvider.h>
#include "unbound.h"

extern "C" {
#include <libuv/uv.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct ub_ctx *ctx = NULL;
  char *name = NULL;
  int rrtype = stream.ConsumeIntegral<int>();
  int rrclass = stream.ConsumeIntegral<int>();
  char *mydata = NULL;
  func_type *callback = NULL;
  int *async_id = NULL;

  ub_ctx_init(ctx);

  size_t name_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  name = new char[name_len + 1];
  stream.ConsumeBytes(name, name_len);
  name[name_len] = '\0';

  int ret = ub_resolve_event(ctx, name, rrtype, rrclass, mydata, callback,
                             async_id);

  delete[] name;
  ub_ctx_delete(ctx);
  return ret;
}