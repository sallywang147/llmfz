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
#include <libssh/ssh.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ssh_session session;
  ssh_key privkey;

  // Initialize the SSH session and key.
  session = ssh_new();
  if (session == NULL) {
    fprintf(stderr, "Error creating SSH session\n");
    return 0;
  }

  if (ssh_key_init(&privkey) != SSH_OK) {
    fprintf(stderr, "Error initializing SSH key\n");
    return 0;
  }

  // Fuzz the SSH session and key.
  FuzzedDataProvider provider(data, size);
  if (provider.ConsumeBool()) {
    // Fuzz the SSH session.
    ssh_options_set(session, SSH_OPTIONS_HOST, provider.ConsumeString(16).c_str());
    ssh_options_set(session, SSH_OPTIONS_PORT, provider.ConsumeIntegral<int>());
    ssh_options_set(session, SSH_OPTIONS_USER, provider.ConsumeString(16).c_str());
  }

  if (provider.ConsumeBool()) {
    // Fuzz the private key.
    if (ssh_pki_import_privkey_file2(&privkey, "id_rsa", NULL, NULL, NULL) != SSH_OK) {
      fprintf(stderr, "Error importing private key\n");
      return 0;
    }
  } else {
    // Fuzz the public key.
    if (ssh_pki_import_pubkey_file(&privkey, "id_rsa.pub", NULL) != SSH_OK) {
      fprintf(stderr, "Error importing public key\n");
      return 0;
    }
  }

  // Authenticate with the SSH server.
  int rc = ssh_userauth_publickey(session, NULL, &privkey);
  if (rc != SSH_AUTH_SUCCESS) {
    fprintf(stderr, "Error authenticating with public key: %s\n", ssh_get_error(session));
  }

  // Disconnect from the SSH server.
  ssh_disconnect(session);
  ssh_free(session);

  // Free the SSH key.
  ssh_key_free(&privkey);

  return 0;
}