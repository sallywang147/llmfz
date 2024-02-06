#include <fuzzer/FuzzedDataProvider.h>
#include <unbound.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ub_ctx* ctx = ub_ctx_create();
  if (!ctx) {
    return 0;
  }

  std::string name = stream.ConsumeRandomLengthString();
  int rrtype = stream.ConsumeIntegral<int>();
  int rrclass = stream.ConsumeIntegral<int>();
  struct ub_result* result;

  ub_resolve(ctx, const_cast<char*>(name.c_str()), rrtype, rrclass, &result);

  ub_resolve_free(result);
  ub_ctx_delete(ctx);

  return 0;
}