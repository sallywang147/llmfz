#include <fuzzer/FuzzedDataProvider.h>
#include <coap3/coap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  coap_context_t *ctx = coap_new_context(nullptr);
  if (ctx == nullptr) {
    return 0;
  }

  coap_address_t local_addr, remote_addr;
  coap_address_init(&local_addr);
  coap_address_init(&remote_addr);

  coap_session_t *session = coap_new_client_session(ctx, &local_addr, &remote_addr, COAP_PROTO_WS);
  if (session == nullptr) {
    coap_free_context(ctx);
    return 0;
  }

  coap_ws_close(session);

  coap_free_context(ctx);
  return 0;
}