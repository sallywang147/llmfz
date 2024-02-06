#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <libssh/libssh.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ssh_init();
    initialized = true;
  }
  int ret;
  ssh_session session = ssh_new();
  if (session == NULL) {
    return 0;
  }

  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");

  ret = ssh_connect(session);
  if (ret != SSH_OK) {
    ssh_free(session);
    return 0;
  }

  ssh_userauth_agent_pubkey(session, nullptr, nullptr);

  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}