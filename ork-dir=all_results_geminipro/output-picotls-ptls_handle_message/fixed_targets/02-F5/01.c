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
  // Initialize the PTLS library.
  PTLS *tls = PTLS_new(PTLS_CLIENT_MODE);
  if (!tls) {
    return 0;
  }

  // Set the PTLS handshake properties.
  PTLS_handshake_properties_t properties;
  PTLS_set_cipher_suites(tls, PTLS_CIPHER_SUITE_AES_128_GCM_SHA256);
  PTLS_set_group(tls, PTLS_GROUP_X25519);
  PTLS_set_version(tls, PTLS_VERSION_1_2);

  // Create a PTLS buffer to hold the input data.
  PTLS_buffer_t input;
  PTLS_buffer_init(&input);
  PTLS_buffer_copy(&input, data, size);

  // Create a PTLS buffer to hold the output data.
  PTLS_buffer_t output;
  PTLS_buffer_init(&output);

  // Handle the input data.
  size_t epoch_offsets[PTLS_MAX_EPOCHS];
  int ret = PTLS_handle_message(tls, &output, epoch_offsets, 0, input.base, input.len, &properties);

  // Clean up.
  PTLS_free(tls);
  PTLS_buffer_free(&input);
  PTLS_buffer_free(&output);

  return 0;
}