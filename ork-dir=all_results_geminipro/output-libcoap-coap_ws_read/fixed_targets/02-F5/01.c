#include <coap3/coap.h>
#include <coap3/coap_ws.h>

extern "C" {
#include <coap3/coap_session.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_session_t *session = coap_new_session(nullptr, nullptr, nullptr);
  if (session) {
    coap_ws_init(session);
    size_t read_bytes = coap_ws_read(session, (char *)data, size);
    coap_ws_cleanup(session);
    coap_free_session(session);
  }
  return 0;
}