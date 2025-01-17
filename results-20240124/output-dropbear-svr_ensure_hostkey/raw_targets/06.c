 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "dropbear.h"
#include "dss.h"
#include "ed25519.h"
#include "fuzz.h"
#include "key.h"
#include "session.h"
#include "signkey.h"
#include "ssh.h"
#include "svr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    fuzz_common_setup();
    initialized = true;
  }
  if (fuzz_set_input(data, size) == DROPBEAR_FAILURE) {
    return 0;
  }

  m_malloc_set_epoch(1);

  if (setjmp(fuzz.jmp) == 0) {
    svr_ensure_hostkey();
  } else {
    m_malloc_free_epoch(1, 1);
    TRACE(("dropbear_exit longjmped"))
    /* dropbear_exit jumped here */
  }

  return 0;
}