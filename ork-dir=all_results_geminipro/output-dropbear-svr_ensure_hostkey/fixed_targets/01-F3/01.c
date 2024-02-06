#include <fuzzer/FuzzedDataProvider.h>
#include <libssh/libssh.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }
  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(session, SSH_OPTIONS_PORT, 22);
  ssh_options_set(session, SSH_OPTIONS_USER, "username");
  ssh_options_set(session, SSH_OPTIONS_TIMEOUT, 10);
  if (ssh_connect(session) != SSH_OK) {
    ssh_free(session);
    return 0;
  }
  ssh_disconnect(session);
  ssh_free(session);
  return 0;
}