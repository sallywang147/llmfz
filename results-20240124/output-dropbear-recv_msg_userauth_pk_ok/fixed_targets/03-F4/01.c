#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <libssh/libssh.h>
#include <libssh/ssh.h>

extern "C" {
#include <libssh/libssh.h>
#include <libssh/ssh.h>
}

int main(int argc, char **argv) {
  ssh_session session = ssh_new();
  if (session == NULL) {
    fprintf(stderr, "Error creating SSH session\n");
    return EXIT_FAILURE;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, argv[1]);
  ssh_options_set(session, SSH_OPTIONS_USER, argv[2]);

  int port = atoi(argv[3]);
  if (port <= 0) {
    fprintf(stderr, "Invalid port number\n");
    return EXIT_FAILURE;
  }
  ssh_options_set(session, SSH_OPTIONS_PORT, &port);

  if (ssh_connect(session) != SSH_OK) {
    fprintf(stderr, "Error connecting to SSH server\n");
    return EXIT_FAILURE;
  }

  ssh_channel channel = ssh_channel_new(session);
  if (channel == NULL) {
    fprintf(stderr, "Error creating SSH channel\n");
    return EXIT_FAILURE;
  }

  if (ssh_channel_open_session(channel) != SSH_OK) {
    fprintf(stderr, "Error opening SSH session\n");
    return EXIT_FAILURE;
  }

  if (ssh_channel_request_auth(channel, SSH_AUTH_METHOD_PUBLICKEY) != SSH_OK) {
    fprintf(stderr, "Error requesting public key authentication\n");
    return EXIT_FAILURE;
  }

  if (ssh_channel_send_auth_publickey(channel, NULL, NULL, 0) != SSH_OK) {
    fprintf(stderr, "Error sending public key authentication\n");
    return EXIT_FAILURE;
  }

  if (ssh_channel_get_exit_status(channel) != SSH_OK) {
    fprintf(stderr, "Error getting SSH channel exit status\n");
    return EXIT_FAILURE;
  }

  ssh_channel_free(channel);
  ssh_disconnect(session);
  ssh_free(session);

  return EXIT_SUCCESS;
}