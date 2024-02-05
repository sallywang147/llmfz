#include <libssh/libssh.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SSH session
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  // Consume data for username and passphrase
  std::string username = stream.ConsumeRandomLengthString();
  std::string passphrase = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  ssh_userauth_publickey_auto(session, const_cast<char*>(username.c_str()), const_cast<char*>(passphrase.c_str()));

  // Cleanup
  ssh_free(session);

  return 0;
}