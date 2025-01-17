#include <libssh/libssh.h>
#include <libssh/server.h>

extern "C" {
#include <libssh/libssh.h>
#include <libssh/server.h>
}

int main() {
  ssh_session session = ssh_new();
  if (session == NULL)
    return 1;

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_PORT, 22);

  if (ssh_connect(session)) {
    ssh_free(session);
    return 1;
  }

  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}