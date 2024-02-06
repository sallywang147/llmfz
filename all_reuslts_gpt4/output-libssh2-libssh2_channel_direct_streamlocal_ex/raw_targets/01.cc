#include "testinput.h"
#include <assert.h>
#include <errno.h>
#include <libssh2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fuzzer/FuzzedDataProvider.h>

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
  LIBSSH2_CHANNEL *channel = NULL;

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

  // FuzzedDataProvider is used to generate fuzzed data.
  FuzzedDataProvider stream(data, size);

  // Extract a string for the socket_path.
  std::string socket_path = stream.ConsumeRandomLengthString();
  char *socket_path_ptr = socket_path.c_str();

  // Extract a string for the shost.
  std::string shost = stream.ConsumeRandomLengthString();
  char *shost_ptr = shost.c_str();

  // Extract an integer for the sport.
  int sport = stream.ConsumeIntegral<int>();

  // Call the target function.
  channel = libssh2_channel_direct_streamlocal_ex(session, socket_path_ptr, shost_ptr, sport);

EXIT_LABEL:

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