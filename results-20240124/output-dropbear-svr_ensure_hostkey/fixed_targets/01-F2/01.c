#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include <libssh/server.h>
}

int main(void) {
  ssh_session session = ssh_new();
  if (session == NULL) {
    fprintf(stderr, "Error creating session\n");
    return EXIT_FAILURE;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_PORT, 22);

  if (ssh_connect(session)) {
    fprintf(stderr, "Error connecting to host\n");
    ssh_free(session);
    return EXIT_FAILURE;
  }

  if (svr_ensure_hostkey(session)) {
    fprintf(stderr, "Error ensuring host key\n");
    ssh_disconnect(session);
    ssh_free(session);
    return EXIT_FAILURE;
  }

  ssh_disconnect(session);
  ssh_free(session);

  return EXIT_SUCCESS;
}