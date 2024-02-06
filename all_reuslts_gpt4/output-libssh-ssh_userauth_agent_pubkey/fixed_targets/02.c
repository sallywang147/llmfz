#include <fuzzer/FuzzedDataProvider.h>
#include "libssh/libssh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ssh_session my_ssh_session = ssh_new();
  if (my_ssh_session == NULL) {
    return 0;
  }

  std::string username = stream.ConsumeRandomLengthString();
  ssh_public_key publickey = ssh_publickey_from_privatekey(my_ssh_session, ssh_key_new());

  ssh_userauth_agent_pubkey(my_ssh_session, username.c_str(), publickey);

  ssh_publickey_free(publickey);
  ssh_free(my_ssh_session);

  return 0;
}