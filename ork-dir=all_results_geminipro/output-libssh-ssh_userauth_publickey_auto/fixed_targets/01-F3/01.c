#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include <libssh/libssh.h>
}

extern "C" ssh_session ssh_new() {
  return ::ssh_new();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_PORT, "22");
  ssh_options_set(session, SSH_OPTIONS_USER, "fuzzer");

  int rc = ssh_connect(session);
  if (rc != SSH_OK) {
    ssh_free(session);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t username_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t passphrase_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> username(username_size + 1);
  std::vector<char> passphrase(passphrase_size + 1);
  provider.ConsumeBytes(username.data(), username_size);
  provider.ConsumeBytes(passphrase.data(), passphrase_size);

  rc = ssh_userauth_publickey_auto(session, username.data(), passphrase.data());
  if (rc != SSH_AUTH_SUCCESS) {
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}