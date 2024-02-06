#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>

extern "C" {
#include <libssh/libssh.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ssh_session session;
  ssh_key privkey;

  int rc = ssh_init();
  if (rc != SSH_OK) {
    return 0;
  }

  session = ssh_new();
  if (session == NULL) {
    ssh_finalize();
    return 0;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");

  FuzzedDataProvider provider(data, size);

  size_t username_len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string username = provider.ConsumeBytesAsString(username_len);

  ssh_pki_init(&privkey);
  size_t key_len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> key_data = provider.ConsumeBytes<uint8_t>(key_len);
  rc = ssh_pki_import_privkey_memory(&privkey, key_data.data(), key_data.size());
  if (rc != SSH_OK) {
    ssh_finalize();
    return 0;
  }

  rc = ssh_connect(session);
  if (rc != SSH_OK) {
    ssh_finalize();
    return 0;
  }

  rc = ssh_userauth_publickey(session, username.c_str(), &privkey);
  if (rc != SSH_AUTH_SUCCESS) {
    ssh_finalize();
    return 0;
  }

  ssh_disconnect(session);
  ssh_free(session);
  ssh_pki_free(&privkey);
  ssh_finalize();

  return 0;
}