#include <libssh/libssh.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SSH session
  ssh_session my_ssh_session = ssh_new();
  if (my_ssh_session == NULL) {
    return 0;
  }

  // Extract username from the fuzz data
  std::string username = stream.ConsumeRandomLengthString();
  if (username.empty()) {
    ssh_free(my_ssh_session);
    return 0;
  }

  // Initialize a new SSH key
  ssh_key my_ssh_privkey;
  int rc = ssh_pki_generate(SSH_KEYTYPE_RSA, 2048, &my_ssh_privkey);
  if (rc != SSH_OK) {
    ssh_free(my_ssh_session);
    return 0;
  }

  // Call the function to fuzz
  ssh_userauth_publickey(my_ssh_session, username.c_str(), my_ssh_privkey);

  // Clean up
  ssh_key_free(my_ssh_privkey);
  ssh_free(my_ssh_session);

  return 0;
}