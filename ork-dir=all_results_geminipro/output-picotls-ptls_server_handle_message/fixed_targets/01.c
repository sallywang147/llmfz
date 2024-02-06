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
  size_t epoch_offsets[PTLS_ELEMENTSOF(ptls_epoch_sizes)];
  size_t in_epoch = 0;
  char input[4096];
  size_t inlen = 0;
  struct st_ptls_handshake_properties_t properties;
  memset(&properties, 0, sizeof(properties));

  ptls_init();
  ptls_set_log_level(PTLS_LOG_ERROR);

  tls = ptls_new(PTLS_SERVER_MODE, PTLS_MT_TLS_1_3);
  if (!tls) {
    ptls_free(tls);
    return 0;
  }

  ptls_buffer_init(&sendbuf);

  ptls_server_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, (char *)data,
                            size, &properties);

  ptls_buffer_dispose(&sendbuf);
  ptls_free(tls);
  ptls_cleanup();

  return 0;
}