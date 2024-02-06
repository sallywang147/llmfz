#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "jq.h"
#include "jv_alloc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize jq state
  jq_state *jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  // Consume data to get size_t a
  size_t a = stream.ConsumeIntegral<size_t>();

  // Create a jv_refcnt struct
  struct jv_refcnt* refcnt = jv_refcnt_init();
  if (refcnt == nullptr) {
    jq_teardown(&jq);
    return 0;
  }

  // Call the function to fuzz
  f_modulemeta(jq, a, refcnt);

  // Cleanup
  jv_refcnt_dec(&refcnt);
  jq_teardown(&jq);

  return 0;
}