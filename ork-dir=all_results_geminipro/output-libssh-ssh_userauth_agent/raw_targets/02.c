#include <fuzzer/FuzzedDataProvider.h>

#include <libssh/libssh.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  ssh_session session = ssh_new();
  ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");

  std::string username = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange(0, 16));
  ssh_userauth_agent(session, username.c_str());

  ssh_free(session);
  return 0;
}