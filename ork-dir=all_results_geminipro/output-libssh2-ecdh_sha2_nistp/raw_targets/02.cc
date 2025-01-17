#include "testinput.h"
#include <assert.h>
#include <errno.h>
#include <libssh2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define FUZZ_ASSERT(COND)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
  if (!(COND)) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
    fprintf(stderr, "Assertion failed: " #COND "\n%s", strerror(errno));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               \
    assert((COND));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    \
  }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int socket_fds[2] = {-1, -1};
  ssize_t written;
  int rc;
  LIBSSH2_SESSION *session = NULL;
  int handshake_completed = 0;
  struct ec_key_st *private_key = NULL;
  struct kmdhgGPshakex_state_t *exchange_state = NULL;

  rc = libssh2_init(0);

  if (rc) {
    fprintf(stderr, "libssh2 initialization failed (%d)\n", rc);
    goto EXIT_LABEL;
  }

  // Create a socket pair so data can be sent in.
  rc = socketpair(AF_UNIX, SOCK_STREAM, 0, socket_fds);
  FUZZ_ASSERT(rc == 0);

  written = send(socket_fds[1], data, size, 0);

  if (written != size) {
    // Handle whatever error case we're in.
    fprintf(stderr, "send() of %zu bytes returned %zu (%d)\n", size, written, errno);
    goto EXIT_LABEL;
  }

  rc = shutdown(socket_fds[1], SHUT_WR);
  if (rc) {
    fprintf(stderr, "socket shutdown failed (%d)\n", rc);
    goto EXIT_LABEL;
  }

  // Create a session and start the handshake using the fuzz data passed in.
  session = libssh2_session_init();
  if (session) {
    libssh2_session_set_blocking(session, 1);
  } else {
    goto EXIT_LABEL;
  }

  if (libssh2_session_handshake(session, socket_fds[0])) {
    goto EXIT_LABEL;
  }

  // If we get here the handshake actually completed.
  handshake_completed = 1;

  // Generate a private key and exchange state.
  private_key = libssh2_ecdh_generate_key(session);
  if (!private_key) {
    fprintf(stderr, "Failed to generate private key\n");
    goto EXIT_LABEL;
  }

  exchange_state = libssh2_ecdh_init(session, private_key);
  if (!exchange_state) {
    fprintf(stderr, "Failed to initialize exchange state\n");
    goto EXIT_LABEL;
  }

  // Fuzz the ecdh_sha2_nistp function.
  rc = ecdh_sha2_nistp(session, 0, NULL, 0, NULL, 0, private_key, exchange_state);
  if (rc != 0) {
    fprintf(stderr, "ecdh_sha2_nistp failed: %d\n", rc);
  }

EXIT_LABEL:

  if (session) {
    if (handshake_completed) {
      libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing");
    }

    libssh2_session_free(session);
  }

  if (private_key) {
    libssh2_ecdh_free(private_key);
  }

  if (exchange_state) {
    libssh2_ecdh_free(exchange_state);
  }

  libssh2_exit();

  close(socket_fds[0]);
  close(socket_fds[1]);

  return 0;
}