#include <fuzzer/FuzzedDataProvider.h>

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

  // Now we can start fuzzing the libssh2_channel_direct_streamlocal_ex function.
  // First, we need to create a channel.
  LIBSSH2_CHANNEL *channel = libssh2_channel_open_session(session);
  if (!channel) {
    fprintf(stderr, "Failed to create channel\n");
    goto EXIT_LABEL;
  }

  // Now we can fuzz the libssh2_channel_direct_streamlocal_ex function.
  FuzzedDataProvider provider(data, size);
  char *socket_path = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange(0, 1024));
  char *shost = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange(0, 1024));
  int sport = provider.ConsumeIntegralInRange<int>(0, 65535);
  LIBSSH2_CHANNEL *direct_channel = libssh2_channel_direct_streamlocal_ex(session, socket_path, shost, sport);
  if (!direct_channel) {
    fprintf(stderr, "Failed to create direct channel\n");
    goto EXIT_LABEL;
  }

  // Now we can send data through the direct channel.
  const char *data_to_send = "Hello, world!";
  size_t data_to_send_len = strlen(data_to_send);
  rc = libssh2_channel_write(direct_channel, data_to_send, data_to_send_len);
  if (rc != data_to_send_len) {
    fprintf(stderr, "Failed to send data through direct channel\n");
    goto EXIT_LABEL;
  }

  // Now we can read data from the direct channel.
  char buffer[1024];
  size_t bytes_read = libssh2_channel_read(direct_channel, buffer, sizeof(buffer));
  if (bytes_read < 0) {
    fprintf(stderr, "Failed to read data from direct channel\n");
    goto EXIT_LABEL;
  }

  // Now we can close the direct channel.
  libssh2_channel_free(direct_channel);

  // Now we can close the channel.
  libssh2_channel_free(channel);

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