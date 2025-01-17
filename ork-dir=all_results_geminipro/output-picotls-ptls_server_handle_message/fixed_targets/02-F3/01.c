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
#include <openssl/ptls.h>

extern "C" {
#include <openssl/ptls.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct st_ptls *tls = NULL;
  struct st_ptls_buffer_t sendbuf;
  size_t epoch_offsets[PTLS_EPOCH_MAX];
  size_t in_epoch = 0;
  struct st_ptls_handshake_properties_t properties;

  ptls_init(&tls, PTLS_SERVER_MODE);
  ptls_buffer_init(&sendbuf);
  ptls_handshake_properties_init(&properties);

  int ret = ptls_server_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, (char *)data, size, &properties);
  assert(ret != PTLS_ERROR_IN_PROGRESS);

  ptls_buffer_dispose(&sendbuf);
  ptls_handshake_properties_free(&properties);
  ptls_free(&tls);
  return 0;
}