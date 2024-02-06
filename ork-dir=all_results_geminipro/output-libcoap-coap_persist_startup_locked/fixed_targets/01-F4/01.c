#include <coap3/coap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <coap3/coap_internal.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  coap_context_t *ctx = coap_new_context(nullptr);
  if (ctx == nullptr) {
    return 0;
  }
  std::string db_path = stream.ConsumeRandomLengthString();
  std::string db_name = stream.ConsumeRandomLengthString();
  std::string db_user = stream.ConsumeRandomLengthString();
  int db_pass_len = stream.ConsumeIntegralInRange<int>(0, 256);
  std::string db_pass = stream.ConsumeBytesAsString(db_pass_len);
  coap_persist_startup_locked(ctx, db_path.c_str(), db_name.c_str(), db_user.c_str(),
                               db_pass_len);
  coap_free_context(ctx);
  return 0;
}