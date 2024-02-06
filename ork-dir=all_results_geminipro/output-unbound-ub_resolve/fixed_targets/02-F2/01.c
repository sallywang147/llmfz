#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "unbound/unbound.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int rrtype = stream.ConsumeIntegral<int>();
  int rrclass = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use `.c_str()` to use result as pointer
  std::string name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
  char *name_ptr = name.c_str();

  // Extract to user defined object
  struct ub_ctx *ctx = ub_ctx_create();

  // Call the function to fuzz
  struct ub_result *result;
  int ret = ub_resolve(ctx, name_ptr, rrtype, rrclass, &result);

  ub_ctx_delete(ctx);
  ub_resolve_free(result);

  return ret;
}