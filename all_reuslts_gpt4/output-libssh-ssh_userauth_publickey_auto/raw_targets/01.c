#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SSH session
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  // Extract username and passphrase from the input data
  std::string username = stream.ConsumeRandomLengthString();
  std::string passphrase = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  ssh_userauth_publickey_auto(session, username.c_str(), passphrase.c_str());

  // Cleanup
  ssh_free(session);

  return 0;
}