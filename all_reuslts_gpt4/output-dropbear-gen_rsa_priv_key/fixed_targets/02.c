#include "fuzz.h"
#include "rsa.h"
#include "dss.h"
#include "fuzz-wrapfd.h"
#include "fuzz.h"
#include "session.h"
#include <fuzzer/FuzzedDataProvider.h>

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
    FuzzedDataProvider stream(Data, Size);
    int size = stream.ConsumeIntegralInRange<int>(512, 4096);
    
    dropbear_DSS_Key *key = gen_rsa_priv_key(size);
    if (key != NULL) {
      mprsa_free(key->rsa);
      m_free(key);
    }
  } else {
    TRACE(("dropbear_exit longjmped"))
    /* dropbear_exit jumped here */
  }

  m_malloc_free_epoch(1, 1);

  return 0;
}