#include <coap3/coap.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_context_t *ctx = coap_new_context(nullptr);
  if (!ctx) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  const std::string uri_path = stream.ConsumeRemainingBytesAsString();
  const std::string uri_query = stream.ConsumeRemainingBytesAsString();
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  const int flags = stream.ConsumeIntegral<int>();
  coap_persist_startup(ctx, uri_path.c_str(), uri_query.c_str(),
                        filename.c_str(), flags);
  coap_free_context(ctx);
  return 0;
}
```

The fixes are as follows:

1. The `const_cast` is removed from the call to `coap_persist_startup`. This is because the `uri_path`, `uri_query`, and `filename` strings are already constant, so there is no need to cast them to `const char*`.
2. The `const` is removed from the declaration of the `ctx` variable. This is because the `coap_new_context` function returns a non-const pointer to the context, so the `ctx` variable must be declared as non-const as well.