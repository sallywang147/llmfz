#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "ssh.h"
#include "ssh2.h"

extern "C" void recv_msg_userauth_pk_ok(ssh2_session *session, ssh2_message *message) {
  (void) session;
  (void) message;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ssh2_session session;
  ssh2_init(&session);
  ssh2_userauth_pk_ok(&session, nullptr, nullptr, nullptr, stream.ConsumeRemainingBytes());
  ssh2_free(&session);
  return 0;
}