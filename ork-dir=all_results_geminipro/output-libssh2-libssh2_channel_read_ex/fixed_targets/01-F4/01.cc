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

extern "C" {
#include <libssh2.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int socket_fds[2] = {-1, -1};
  ssize_t written;
  int rc;
  LIBSSH2_SESSION *session = NULL;
  LIBSSH2_CHANNEL *channel = NULL;
  int handshake_completed = 0;

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

  // Open a channel
  channel = libssh2_channel_open_session(session);
  if (!channel) {
    goto EXIT_LABEL;
  }

  // Execute a command on the remote host
  rc = libssh2_channel_exec(channel, "ls");
  if (rc != 0) {
    goto EXIT_LABEL;
  }

  // Read the output of the command
  char buffer[1024];
  size_t bytes_read;
  while ((bytes_read = libssh2_channel_read_ex(channel, 0, buffer, sizeof(buffer)))) {
    // Do something with the data
  }

EXIT_LABEL:

  if (channel) {
    libssh2_channel_free(channel);
  }

  if (session) {
    if (handshake_completed) {
      libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing");
    }

    libssh2_session_free(session);
  }

  libssh2_exit();

  close(socket_fds[0]);
  close(socket_fds[1]);

  return 0;
}