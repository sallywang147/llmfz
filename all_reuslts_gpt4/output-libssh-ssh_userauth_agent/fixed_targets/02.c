#include <libssh/libssh.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SSH session
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  // Consume fuzzing data to generate username
  std::string username = stream.ConsumeRandomLengthString();
  if (username.empty()) {
    ssh_free(session);
    return 0;
  }

  // Call the function to be fuzzed
  ssh_userauth_agent(session, const_cast<char*>(username.c_str()));

  // Cleanup
  ssh_free(session);

  return 0;
}