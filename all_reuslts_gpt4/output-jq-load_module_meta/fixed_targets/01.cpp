#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "jq.h"
#include "jv.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the jq_state
  jq_state *jq = jq_init();
  if (jq == NULL) {
    return 0;
  }

  // Consume data for mod_relpath
  size_t mod_relpath = stream.ConsumeIntegral<size_t>();

  // Initialize jv_refcnt
  struct jv_refcnt *refcnt = jv_refcnt_init();

  // Call the target function
  load_module_meta(jq, mod_relpath, refcnt);

  // Cleanup
  jq_teardown(&jq);
  jv_refcnt_dec(&refcnt);

  return 0;
}