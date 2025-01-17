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
#include <openssl/evp.h>
#include <openssl/pem.h>

#include "picotls.h"
#include "picotls/openssl.h"
#include "util.h"

extern "C" {
#include "picotls/openssl/picotls_openssl.h"
}

void deterministic_random_bytes(void *buf, size_t len) {
  for (int i = 0; i < len; i++) {
    ((uint8_t *)buf)[i] = i;
  }
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ptls_context_t *ctx = ptls_context_new(PTLS_DEFAULT_PSK_KEY_SIZE,
                                          PTLS_DEFAULT_PSK_IDENTITY_SIZE);
  if (!ctx) {
    return -1;
  }
  ptls_context_set_random_bytes_callback(ctx, deterministic_random_bytes);
  ptls_t *tls = ptls_new(ctx, PTLS_CLIENT_MODE);
  if (!tls) {
    ptls_context_free(ctx);
    return -1;
  }

  ptls_buffer_t sendbuf;
  ptls_buffer_init(&sendbuf, data, size);

  /* This is the function that the fuzzer is complaining about. */
  ptls_send(tls, &sendbuf, NULL, 0);

  ptls_buffer_dispose(&sendbuf);
  ptls_free(tls);
  ptls_context_free(ctx);
  return 0;
}