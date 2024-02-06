#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SSH session
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  // Extract username from the stream
  std::string username = stream.ConsumeRandomLengthString();
  if (username.empty()) {
    ssh_free(session);
    return 0;
  }

  // Create a public key
  ssh_key publickey;
  if (ssh_pki_generate(SSH_KEYTYPE_RSA, 2048, &publickey) != SSH_OK) {
    ssh_free(session);
    return 0;
  }

  // Call the target function
  ssh_userauth_agent_pubkey(session, username.c_str(), publickey);

  // Cleanup
  ssh_key_free(publickey);
  ssh_free(session);

  return 0;
}