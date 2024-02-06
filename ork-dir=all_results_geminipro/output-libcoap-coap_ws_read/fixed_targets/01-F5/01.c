#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "coap.h"
#include "coap_ws.h"

extern "C" {
#include "coap_fuzz.h"
}

size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_context_t *ctx;
  coap_session_t *session;
  coap_pdu_t *pdu;
  unsigned char buf[2048];
  size_t len;

  ctx = coap_new_context(NULL);
  if (!ctx) {
    return 0;
  }

  session = coap_new_client_session(ctx, NULL, 0);
  if (!session) {
    coap_free_context(ctx);
    return 0;
  }

  pdu = coap_pdu_init(COAP_MESSAGE_CON, COAP_REQUEST_GET, coap_new_message_id(session), COAP_DEFAULT_MAX_MESSAGE_SIZE);
  if (!pdu) {
    coap_free_session(session);
    coap_free_context(ctx);
    return 0;
  }

  coap_add_option(pdu, COAP_OPTION_URI_PATH, strlen("/"), (unsigned char *)"/");

  len = coap_ws_write(session, pdu, buf, sizeof(buf));
  if (len == 0) {
    coap_free_pdu(pdu);
    coap_free_session(session);
    coap_free_context(ctx);
    return 0;
  }

  // Read the response.
  size_t read_len = coap_ws_read(session, buf, sizeof(buf));
  if (read_len == 0) {
    coap_free_pdu(pdu);
    coap_free_session(session);
    coap_free_context(ctx);
    return 0;
  }

  coap_free_pdu(pdu);
  coap_free_session(session);
  coap_free_context(ctx);

  return 0;
}