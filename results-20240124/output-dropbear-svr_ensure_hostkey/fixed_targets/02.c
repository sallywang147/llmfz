#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>
#include <libssh/server.h>

extern "C" {
#include <libssh/libssh.h>
#include <libssh/server.h>
}

void svr_ensure_hostkey() {
  ssh_bind_options_set(NULL, SSH_BIND_OPTIONS_RSAKEY, "/tmp/id_rsa");
  ssh_bind_options_set(NULL, SSH_BIND_OPTIONS_DSAKEY, "/tmp/id_dsa");
  ssh_bind_options_set(NULL, SSH_BIND_OPTIONS_ECDSAKEY, "/tmp/id_ecdsa");
  ssh_bind_options_set(NULL, SSH_BIND_OPTIONS_ED25519KEY, "/tmp/id_ed25519");
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  ssh_session session = ssh_new();
  if (session == NULL)
    return 0;

  ssh_bind_options_set(session, SSH_BIND_OPTIONS_RSAKEY, "/tmp/id_rsa");
  ssh_bind_options_set(session, SSH_BIND_OPTIONS_DSAKEY, "/tmp/id_dsa");
  ssh_bind_options_set(session, SSH_BIND_OPTIONS_ECDSAKEY, "/tmp/id_ecdsa");
  ssh_bind_options_set(session, SSH_BIND_OPTIONS_ED25519KEY, "/tmp/id_ed25519");

  ssh_server_options_set(session, SSH_SERVER_OPTIONS_HOSTKEY, "/tmp/id_rsa");
  ssh_server_options_set(session, SSH_SERVER_OPTIONS_RSAKEY, "/tmp/id_rsa");
  ssh_server_options_set(session, SSH_SERVER_OPTIONS_DSAKEY, "/tmp/id_dsa");
  ssh_server_options_set(session, SSH_SERVER_OPTIONS_ECDSAKEY, "/tmp/id_ecdsa");
  ssh_server_options_set(session, SSH_SERVER_OPTIONS_ED25519KEY, "/tmp/id_ed25519");

  svr_ensure_hostkey();

  ssh_server_start(session);
  ssh_server_join(session);
  ssh_get_error(session);
  ssh_server_free(session);
  return 0;
}