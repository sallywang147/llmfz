#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <libssh/libssh.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a session.
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  // Initialize the session.
  int rc = ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  if (rc != SSH_OK) {
    ssh_free(session);
    return 0;
  }

  // Connect to the server.
  rc = ssh_connect(session);
  if (rc != SSH_OK) {
    ssh_free(session);
    return 0;
  }

  // Authenticate the user.
  rc = ssh_userauth_agent_publickey(session, nullptr, nullptr);
  if (rc != SSH_AUTH_SUCCESS) {
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  // Close the session.
  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}