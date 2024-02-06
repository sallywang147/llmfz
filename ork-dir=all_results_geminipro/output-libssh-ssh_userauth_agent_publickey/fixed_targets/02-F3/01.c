#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include <libssh/libssh.h>
}

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

  // Execute a command.
  const char* command = provider.ConsumeRandomLengthString(100).c_str();
  ssh_channel channel = ssh_channel_new(session);
  if (channel == NULL) {
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK) {
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  rc = ssh_channel_request_exec(channel, command);
  if (rc != SSH_OK) {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  // Read the output of the command.
  std::vector<char> output;
  while (true) {
    char buffer[1024];
    int nread = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    if (nread < 0) {
      break;
    }
    output.insert(output.end(), buffer, buffer + nread);
  }

  // Close the channel and the session.
  ssh_channel_send_eof(channel);
  ssh_channel_close(channel);
  ssh_channel_free(channel);
  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}