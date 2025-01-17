#include <libssh/libssh.h>
#include <libssh/server.h>

extern "C" {
#include <libssh/server.h>
}

void svr_ensure_hostkey(void);

int main(int argc, char **argv) {
  ssh_bind sshbind;
  sshbind.port = 22;
  sshbind.bind_address = "0.0.0.0";
  int verbosity = SSH_LOG_PROTOCOL;
  ssh_server server;

  svr_ensure_hostkey();

  ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY, "/etc/ssh/ssh_host_rsa_key");
  ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_DSAKEY, "/etc/ssh/ssh_host_dsa_key");

  ssh_server_options_set(server, SSH_SERVER_OPTIONS_BIND, &sshbind);
  ssh_server_options_set(server, SSH_SERVER_OPTIONS_LOG_VERBOSITY, &verbosity);
  ssh_server_options_set(server, SSH_SERVER_OPTIONS_HOSTKEY, "/etc/ssh/ssh_host_rsa_key");

  if (ssh_server_start(&server) != SSH_OK) {
    fprintf(stderr, "Error starting server: %s\n", ssh_get_error(&server));
    return 1;
  }

  ssh_server_join(&server);
  ssh_server_free(&server);

  return 0;
}