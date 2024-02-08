#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <libssh/libssh.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ssh_session session;
  int rc;

  session = ssh_new();
  if (session == NULL) {
    fprintf(stderr, "Error creating session: %s\n", ssh_get_error(session));
    return 0;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_PORT, "22");

  rc = ssh_connect(session);
  if (rc != SSH_OK) {
    fprintf(stderr, "Error connecting to server: %s\n", ssh_get_error(session));
    ssh_free(session);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  size_t username_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  size_t passphrase_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> username_bytes = provider.ConsumeBytes<uint8_t>(username_length);
  std::vector<uint8_t> passphrase_bytes = provider.ConsumeBytes<uint8_t>(passphrase_length);
  char* username = reinterpret_cast<char*>(username_bytes.data());
  char* passphrase = reinterpret_cast<char*>(passphrase_bytes.data());

  rc = ssh_userauth_publickey_auto(session, username, passphrase);
  if (rc != SSH_AUTH_SUCCESS) {
    fprintf(stderr, "Error authenticating with public key: %s\n", ssh_get_error(session));
  }

  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}