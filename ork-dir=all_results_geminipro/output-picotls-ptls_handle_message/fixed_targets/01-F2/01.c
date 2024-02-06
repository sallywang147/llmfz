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
  struct st_ptls_t *tls = NULL;
  struct st_ptls_buffer_t sendbuf;
  size_t epoch_offsets[100];
  struct st_ptls_handshake_properties_t properties;
  ptls_handshake_properties_init(&properties);

  ptls_init(PTLS_SERVER_MODE, &tls);
  ptls_buffer_init(&sendbuf, 8192);

  ptls_handle_message(tls, &sendbuf, epoch_offsets, 0, (char *)data, size, &properties);

  ptls_buffer_dispose(&sendbuf);
  ptls_free(&tls);
  ptls_handshake_properties_free(&properties);
  return 0;
}