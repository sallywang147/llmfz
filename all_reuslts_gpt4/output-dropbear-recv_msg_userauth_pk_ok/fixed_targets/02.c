#include "debug.h"
#include "fuzz-wrapfd.h"
#include "fuzz.h"
#include "session.h"

static void setup_fuzzer(void) {
  fuzz_common_setup();

  /* Avoid hitting exit() for cases when the fuzzer generates known_hosts
  with a null filename */
  fuzz.skip_file = 1;

  svr_opts.banner = "";

  /* Ensure that buf_match_algo is happy */
  svr_opts.algos = gen_algos();

  /* We're running as a server */
  svr_opts.hostkey = "fuzz-hk";
  fuzz_run_setup();

  /* setup the session */
  ses.authstate = AUTH_NONE;
  ses.newkeys = 0;
  /* This makes us hit the preauth case */
  svr_ses.childpid = 0;
  svr_ses.childpipe = -1;

  /* setup the IO buffers */
  ses.writepayload = buf_new(MAX_PAYLOAD_LEN);
  ses.readbuf = buf_new(MAX_PAYLOAD_LEN);
  ses.payload = buf_new(MAX_PAYLOAD_LEN);
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
  } else {
    TRACE(("dropbear_exit longjmped"))
    /* dropbear_exit jumped here */
  }

  m_malloc_free_epoch(1, 1);

  return 0;
}