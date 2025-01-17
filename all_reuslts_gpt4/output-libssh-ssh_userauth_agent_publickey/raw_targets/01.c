#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SSH session
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  // Consume fuzzed data to initialize parameters
  std::string username = stream.ConsumeRandomLengthString();
  ssh_key pubkey;
  int rc = ssh_pki_generate(SSH_KEYTYPE_RSA, 2048, &pubkey);
  if (rc != SSH_OK) {
    ssh_free(session);
    return 0;
  }

  // Call the function to fuzz
  ssh_userauth_agent_publickey(session, username.c_str(), pubkey);

  // Cleanup
  ssh_key_free(pubkey);
  ssh_free(session);

  return 0;
}