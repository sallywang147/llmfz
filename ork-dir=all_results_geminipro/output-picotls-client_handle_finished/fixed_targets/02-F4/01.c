#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <openssl/engine.h>
#include <openssl/err.h>

extern "C" {
#include <ptls/ptls.h>
}

int client_handle_finished(struct st_ptls_t * tls, struct st_ptls_message_emitter_t * emitter, char * message, size_t message_size) {
  int ret;
  ret = ptls_handshake_client_finished(tls, emitter, message, message_size);
  return ret;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int ret;
  struct st_ptls_t *tls;
  struct st_ptls_message_emitter_t *emitter;
  char message[4096];

  tls = ptls_new(PTLS_CLIENT_MODE, PTLS_MTU_1350);
  assert(tls != NULL);

  emitter = ptls_get_message_emitter(tls);
  assert(emitter != NULL);

  ret = client_handle_finished(tls, emitter, message, size);
  assert(ret == 0);

  ptls_free(tls);

  return 0;
}

int main() {
  return 0;
}