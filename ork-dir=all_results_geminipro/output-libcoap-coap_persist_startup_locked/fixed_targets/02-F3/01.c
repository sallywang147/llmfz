#include <coap3/coap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
#include <coap3/coap.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_context_t *ctx = coap_new_context(NULL);
  if (!ctx) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string path = stream.ConsumeRemainingBytesAsString();

  int ret = coap_persist_startup_locked(ctx, NULL, NULL, path.c_str(), 0);
  if (ret == 0) {
    coap_delete_context(ctx);
  }

  return 0;
}