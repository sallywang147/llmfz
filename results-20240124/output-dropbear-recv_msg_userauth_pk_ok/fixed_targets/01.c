#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <libssh2.h>
#include <libssh2_sftp.h>

extern "C" {
#include <libssh2.h>
#include <libssh2_sftp.h>
}

int main(int argc, char **argv) {
  // ...
  return 0;
}

void recv_msg_userauth_pk_ok(LIBSSH2_SESSION *session) {
  // ...
}