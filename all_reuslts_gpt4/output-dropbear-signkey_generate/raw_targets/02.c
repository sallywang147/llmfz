#include "debug.h"
#include "dss.h"
#include "ed25519.h"
#include "fuzz-wrapfd.h"
#include "fuzz.h"
#include "session.h"
#include <fuzzer/FuzzedDataProvider.h>

static void setup_fuzzer(void) { fuzz_common_setup(); }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static int once = 0;
  if (!once) {
    setup_fuzzer();
    once = 1;
  }

  FuzzedDataProvider stream(data, size);
  
  m_malloc_set_epoch(1);

  if (setjmp(fuzz.jmp) == 0) {
    int keytype = stream.ConsumeIntegral<int>();
    int bits = stream.ConsumeIntegral<int>();
    std::string filename = stream.ConsumeRemainingBytesAsString();
    int skip_exist = stream.ConsumeBool();

    signkey_generate(keytype, bits, filename.c_str(), skip_exist);
    
    m_malloc_free_epoch(1, 0);
  } else {
    m_malloc_free_epoch(1, 1);
    TRACE(("dropbear_exit longjmped"))
    /* dropbear_exit jumped here */
  }

  return 0;
}