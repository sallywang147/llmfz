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
  ssh_session session;
  session = ssh_new();
  if (session == NULL) {
    fprintf(stderr, "Error creating SSH session\n");
    return 0;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");

  ssh_key privkey;
  ssh_key_init(&privkey);

  FuzzedDataProvider provider(data, size);
  if (provider.ConsumeBool()) {
    // Fuzz the private key.
    ssh_pki_import_privkey_file2(&privkey, "id_rsa", NULL, NULL, NULL);
  } else {
    // Fuzz the public key.
    ssh_pki_import_pubkey_file(&privkey, "id_rsa.pub", NULL);
  }

  int rc = ssh_userauth_publickey(session, NULL, &privkey);
  if (rc != SSH_AUTH_SUCCESS) {
    fprintf(stderr, "Error authenticating with public key: %s\n", ssh_get_error(session));
  }

  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}