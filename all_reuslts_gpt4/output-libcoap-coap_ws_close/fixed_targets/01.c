#include <fuzzer/FuzzedDataProvider.h>

#include <coap3/coap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize CoAP context and session
  coap_context_t *ctx = coap_new_context(nullptr);
  if (ctx == nullptr) {
    return 0;
  }

  coap_address_t addr;
  coap_address_init(&addr);
  addr.addr.sin.sin_family = AF_INET;

  coap_session_t *session = coap_new_client_session(ctx, nullptr, &addr, COAP_PROTO_WS);
  if (session == nullptr) {
    coap_free_context(ctx);
    return 0;
  }

  // Call the function under test
  coap_ws_close(session);

  // Clean up
  coap_free_context(ctx);

  return 0;
}