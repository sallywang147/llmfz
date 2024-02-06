#include "debug.h"
#include "dss.h"
#include "ed25519.h"
#include "fuzz-wrapfd.h"
#include "fuzz.h"
#include "session.h"

static void setup_fuzzer(void) { fuzz_common_setup(); }

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
    svr_ensure_hostkey();
    m_malloc_free_epoch(1, 0);
  } else {
    m_malloc_free_epoch(1, 1);
    TRACE(("dropbear_exit longjmped"))
    /* dropbear_exit jumped here */
  }

  return 0;
}