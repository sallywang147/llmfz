#include <coap3/coap.h>

extern "C" {
#include <coap3/coap_ws.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_ws_session_t *session = coap_ws_new_client_session(NULL, NULL, NULL, 0);
  if (session) {
    coap_ws_close(session);
    coap_ws_free_session(session);
  }
  return 0;
}
```

Changes made:
1. Changed `coap_session_t` to `coap_ws_session_t` in the declaration of `session`.
2. Changed `coap_new_client_session` to `coap_ws_new_client_session` in the call to create the session.
3. Changed `coap_free_session` to `coap_ws_free_session` in the call to free the session.