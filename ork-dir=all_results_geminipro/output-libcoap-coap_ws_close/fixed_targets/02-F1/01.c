#include <coap3/coap.h>

extern "C" {
#include <coap3/coap_ws.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_session_t *session = coap_new_client_session(NULL, NULL, NULL, 0);
  if (session) {
    coap_ws_close(session);
    coap_free_session(session);
  }
  return 0;
}