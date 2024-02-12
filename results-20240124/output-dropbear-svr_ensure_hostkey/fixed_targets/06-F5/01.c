#include <stdio.h>
#include <libssh/libssh.h>

extern "C" {
#include <libssh/sftp.h>
}

int main() {
  ssh_session my_ssh_session = ssh_new();
  if (my_ssh_session == NULL)
    exit(-1);

  ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "ssh.example.com");
  ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "username");

  if (ssh_connect(my_ssh_session)) {
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    exit(-1);
  }

  if (svr_ensure_hostkey(my_ssh_session)) {
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    exit(-1);
  }

  ssh_disconnect(my_ssh_session);
  ssh_free(my_ssh_session);
  return 0;
}