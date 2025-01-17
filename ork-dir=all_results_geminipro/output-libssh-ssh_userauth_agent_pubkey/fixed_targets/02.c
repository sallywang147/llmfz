#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <libssh/libssh.h>

extern "C" {
#include <libssh/libssh.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_USER, "username");
  ssh_options_set(session, SSH_OPTIONS_PORT, 22);

  int rc = ssh_connect(session);
  if (rc != SSH_OK) {
    ssh_free(session);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string username = provider.ConsumeRandomLengthString(1024);
  std::vector<uint8_t> key_data = provider.ConsumeRemainingBytes();
  ssh_key key = ssh_key_new();
  if (ssh_key_from_private(key, key_data.data(), key_data.size()) != SSH_OK) {
    ssh_key_free(key);
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  rc = ssh_userauth_agent_pubkey(session, username.c_str(), key);
  if (rc != SSH_AUTH_SUCCESS) {
    ssh_key_free(key);
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  ssh_key_free(key);
  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}