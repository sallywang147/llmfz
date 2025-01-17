#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ssh session
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  // Extract a string from the fuzz data provider
  std::string username = stream.ConsumeRandomLengthString();
  
  // Call the function to fuzz
  ssh_userauth_agent(session, username.c_str());

  // Clean up
  ssh_free(session);

  return 0;
}