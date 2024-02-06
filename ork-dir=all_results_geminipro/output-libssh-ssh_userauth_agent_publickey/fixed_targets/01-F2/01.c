#include <fuzzer/FuzzedDataProvider.h>

#include <libssh/libssh.h>

extern "C" {
#include <libssh/libssh.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }
  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_USER, "user");
  ssh_options_set(session, SSH_OPTIONS_PORT, 22);
  ssh_options_set(session, SSH_OPTIONS_TIMEOUT, 10);
  ssh_options_set(session, SSH_OPTIONS_CIPHERS, "aes128-ctr,aes192-ctr,aes256-ctr");
  ssh_options_set(session, SSH_OPTIONS_HOSTKEYS, "ssh-rsa,ssh