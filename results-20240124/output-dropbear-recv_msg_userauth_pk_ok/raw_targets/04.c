 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "buffer.h"
#include "common.h"
#include "dbutil.h"
#include "log.h"
#include "network.h"
#include "session.h"
#include "ssh.h"
#include "ssh2.h"
#include "sshbuf.h"
#include "userauth.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string username = stream.ConsumeRemainingBytesAsString();
  const buffer* username_buf = buf_new((const void*)username.c_str(), username.size());

  ssh_session session;
  memset(&session, 0, sizeof(session));
  session.authstate.auth_methods = SSH2_AUTH_METHOD_PUBLICKEY;
  session.authstate.auth_tried = SSH2_AUTH_METHOD_PUBLICKEY;
  session.authstate.username = username_buf;
  session.authstate.pw_auth_pw = nullptr;
  session.authstate.pw_auth_pwlen = 0;
  session.authstate.pw_auth_pw_hash = nullptr;

  recv_msg_userauth_pk_ok(&session);

  buf_free(session.authstate.username);
  return 0;
}