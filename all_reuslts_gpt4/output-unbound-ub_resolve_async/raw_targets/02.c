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
  std::string mydata = stream.ConsumeRandomLengthString();
  int async_id = 0;

  ub_resolve_async(ctx, const_cast<char*>(name.c_str()), rrtype, rrclass, const_cast<char*>(mydata.c_str()), nullptr, &async_id);
  
  ub_ctx_delete(ctx);
  
  return 0;
}