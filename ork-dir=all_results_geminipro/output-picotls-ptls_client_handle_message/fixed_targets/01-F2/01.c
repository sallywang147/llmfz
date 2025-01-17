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

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct st_ptls *tls = NULL;
  struct st_ptls_buffer_t sendbuf;
  size_t epoch_offsets[10];
  size_t in_epoch = 0;
  struct st_ptls_handshake_properties_t properties;

  ptls_handshake_properties_init(&properties);

  ptls_init(PTLS_CLIENT_MODE, &tls, &sendbuf, epoch_offsets, 10, &properties);

  ptls_client_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, (char *)data, size, &properties);

  ptls_free(tls);

  return 0;
}