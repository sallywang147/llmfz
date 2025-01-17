#include "debug.h"
#include "fuzz.h"
#include "session.h"

static void setup_fuzzer(void) {
  fuzz_common_setup();
  svr_ses.state = SSH_SENT_PK_OK;
  svr_ses.kexstate.donefirstkex = 1;
  svr_ses.authstate.authdone = 0;
  svr_ses.authstate.authtypes = AUTH_TYPE_PUBKEY;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  static int once = 0;
  if (!once) {
    setup_fuzzer();
    once = 1;
  }

  if (fuzz_set_input(Data, Size) == DROPBEAR_FAILURE) {
    return 0;
  }

  m_malloc_set_epoch(1);

  if (setjmp(fuzz.jmp) == 0) {
    recv_msg_userauth_pk_ok();
  }

  m_malloc_free_epoch(1, 1);

  return 0;
}