#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jq.h"
#include "jv.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize jq state
  jq_state *jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  // Consume size_t from the stream
  size_t a = stream.ConsumeIntegral<size_t>();

  // Initialize jv_refcnt
  struct jv_refcnt *refcnt = jv_refcnt_init();
  if (refcnt == nullptr) {
    jq_teardown(&jq);
    return 0;
  }

  // Call the target function
  f_modulemeta(jq, a, refcnt);

  // Clean up
  jv_refcnt_dec(&refcnt);
  jq_teardown(&jq);

  return 0;
}