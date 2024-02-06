#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <libssh/libssh.h>

extern "C" {
#include <libssh/libssh.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ssh_session session;
  ssh_channel channel;
  ssh_public_key pubkey;
  int rc;

  session = ssh_new();
  if (session == NULL)