#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>

extern "C" {
#include <libssh/libssh.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }
  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");

  FuzzedDataProvider provider(data, size);
  size_t username_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string username = provider.ConsumeBytesAsString(username_length);

  int rc = ssh_userauth_agent(session, username.c_str());
  if (rc != SSH_AUTH_SUCCESS) {
    ssh_disconnect(session);
    ssh_free(session);
    return 0;
  }

  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}