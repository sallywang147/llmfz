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
  coap_persist_startup(ctx, const_cast<char*>(uri_path.c_str()),
                        const_cast<char*>(uri_query.c_str()),
                        const_cast<char*>(filename.c_str()), flags);
  coap_free_context(ctx);
  return 0;
}