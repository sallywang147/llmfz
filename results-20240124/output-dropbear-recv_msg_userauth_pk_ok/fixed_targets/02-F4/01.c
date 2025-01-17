#include <stddef.h>
#include <stdint.h>

#include <dropbear/dropbear.h>

extern "C" {
#include <dropbear/dropbear.h>
#include <dropbear/dropbear_messages.h>
#include <dropbear/dropbear_session.h>
#include <dropbear/dropbear_srvr.h>
#include <dropbear/dropbear_util.h>
}

void recv_msg_userauth_pk_ok(struct dropbear_session *session) {
  dropbear_log(LOG_INFO, "recv_msg_userauth_pk_ok");
  dropbear_exit(session);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  recv_msg_userauth_pk_ok(NULL);
  return 0;
}