#include <fuzzer/FuzzedDataProvider.h>
#include <unbound.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ub_ctx* ctx = ub_ctx_create();
  if(!ctx) {
    return 0;
  }

  // Consume data to create a name
  std::string name = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  // Consume data to create rrtype and rrclass
  int rrtype = stream.ConsumeIntegral<int>();
  int rrclass = stream.ConsumeIntegral<int>();

  struct ub_result* result;

  int ret = ub_resolve(ctx, strdup(name.c_str()), rrtype, rrclass, &result);
  if(ret == 0) {
    ub_resolve_free(result);
  }

  ub_ctx_delete(ctx);

  return 0;
}