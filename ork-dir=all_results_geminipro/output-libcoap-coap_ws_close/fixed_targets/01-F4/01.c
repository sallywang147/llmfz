#include <coap3/coap.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <coap3/ws.h>
#ifdef __cplusplus
}
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_session_t *session = coap_new_session(NULL, NULL, COAP_PROTO_UDP);
  if (session) {
    coap_ws_close(session);
    coap_free_session(session);
  }
  return 0;
}