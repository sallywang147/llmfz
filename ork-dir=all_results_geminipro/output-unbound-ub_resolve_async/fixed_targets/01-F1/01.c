#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unbound.h"

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct ub_ctx *ctx = NULL;
  char *name = NULL;
  int rrtype = 0;
  int rrclass = 0;
  char *mydata = NULL;
  func_type *callback = NULL;
  int *async_id = NULL;

  FuzzedDataProvider stream(data, size);

  if (size < 1) return 0;
  size_t name_size = stream.ConsumeIntegralInRange(1, size);
  name = (char *)malloc(name_size);
  stream.ConsumeBytes(name, name_size);

  rrtype = stream.ConsumeIntegralInRange(0, 100);
  rrclass = stream.ConsumeIntegralInRange(0, 100);

  size_t mydata_size = stream.ConsumeIntegralInRange(0, size);
  mydata = (char *)malloc(mydata_size);
  stream.ConsumeBytes(mydata, mydata_size);

  callback = (func_type *)malloc(sizeof(func_type));
  *callback = NULL;

  async_id = (int *)malloc(sizeof(int));
  *async_id = 0;

  ub_resolve_async(ctx, name, rrtype, rrclass, mydata, callback, async_id);

  free(name);
  free(mydata);
  free(callback);
  free(async_id);

  return 0;
}