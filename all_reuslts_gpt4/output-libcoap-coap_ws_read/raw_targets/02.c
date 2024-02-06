#include <fuzzer/FuzzedDataProvider.h>
#include <coap3/coap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create coap context and session
  coap_context_t *ctx = coap_new_context(nullptr);
  if (ctx == nullptr) {
    return 0;
  }

  coap_address_t dst;
  coap_address_init(&dst);
  dst.addr.sa.sa_family = AF_INET;
  dst.size = sizeof(dst.addr.sin);

  coap_session_t *session = coap_new_client_session(ctx, nullptr, &dst, COAP_PROTO_WS);
  if (session == nullptr) {
    coap_free_context(ctx);
    return 0;
  }

  // Consume data to read
  size_t read_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> read_data = stream.ConsumeBytes<char>(read_size);

  // Call the function
  coap_ws_read(session, read_data.data(), read_size);

  // Clean up
  coap_free_context(ctx);

  return 0;
}