#include <coap3/coap.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize coap library
  coap_startup();

  coap_context_t *ctx = coap_new_context(nullptr);
  if (ctx == nullptr) {
    coap_cleanup();
    return 0;
  }

  coap_address_t addr;
  coap_address_init(&addr);
  addr.addr.sin.sin_family = AF_INET;
  addr.addr.sin.sin_port = htons(5683);
  addr.addr.sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  coap_session_t *session = coap_new_client_session(ctx, nullptr, &addr, COAP_PROTO_WS);
  if (session == nullptr) {
    coap_free_context(ctx);
    coap_cleanup();
    return 0;
  }

  const size_t read_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> read_buffer(read_size);
  coap_ws_read(session, read_buffer.data(), read_size);

  coap_free_context(ctx);
  coap_cleanup();

  return 0;
}