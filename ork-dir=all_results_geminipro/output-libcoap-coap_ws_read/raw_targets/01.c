#include <coap3/coap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_session_t *session = coap_new_client_session(NULL, NULL, NULL);
  if (session) {
    size_t read_size = coap_ws_read(session, (char *)data, size);
    coap_free_session(session);
  }
  return 0;
}